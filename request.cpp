#include "request.h"
#include "responsefile.h"
#include "responsedirectory.h"
#include "log.h"
#include "settings.h"

#include <QHostAddress>
#include <QTextStream>
#include <QStringList>
#include <QFileInfo>
#include <QDateTime>

//defination here
QString Request::s_root_path;
QStringList Request::s_index;
bool Request::s_dir_listing;
bool Request::s_keep_alive_enable;
bool Request::s_keep_alive_default;
int Request::s_keep_alive_timeout;
int Request::s_keep_alive_timeout_max;
bool Request::s_initialized = false;

void Request::initialize()
{
    s_initialized = true;
    bool ok;
    s_root_path = Settings::instance().value("site/root_path").toString();
    s_index = Settings::instance().value("site/index").toStringList();
    s_dir_listing = Settings::instance().value("site/dir_listing", DEFAULT_SITE_DIR_LISTING).toBool();

    s_keep_alive_enable = Settings::instance().value("request/keep_alive_enable", DEFAULT_REQUEST_KEEP_ALIVE_ENABLE).toBool();
    s_keep_alive_default = Settings::instance().value("request/keep_alive_default", DEFAULT_REQUEST_KEEP_ALIVE_DEFAULT).toBool();

    s_keep_alive_timeout = Settings::instance().value("request/keep_alive_timeout", DEFAULT_REQUEST_KEEP_ALIVE_TIMEOUT).toUInt(&ok);
    if (!ok)
        s_keep_alive_timeout = DEFAULT_REQUEST_KEEP_ALIVE_TIMEOUT;

    s_keep_alive_timeout_max = Settings::instance().value("request/keep_alive_timeout_max", DEFAULT_REQUEST_KEEP_ALIVE_TIMEOUT_MAX).toUInt(&ok);
    if (!ok)
        s_keep_alive_timeout_max = DEFAULT_REQUEST_KEEP_ALIVE_TIMEOUT_MAX;
}

Request::Request(int socketDescriptor, QObject* parent):
    QThread(parent), response(NULL)
{
    if (!s_initialized)
        initialize();
    this->socketDescriptor = socketDescriptor;
    connect(this, SIGNAL(finished()), this, SLOT(deleteLater()));

    if (s_keep_alive_enable)
    {
        keep_alive = s_keep_alive_default;
        keep_alive_timeout = s_keep_alive_timeout * 1000;
        connect(&keep_alive_timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
        keep_alive_timer.setSingleShot(true);
        keep_alive_timer.setInterval(keep_alive_timeout);
        keep_alive_timer.start();
    }
}

void Request::clearStatus()
{
    delete response;
    response = NULL;
    response_header.clear();
    request_header.clear();
    response_code = 0;
    response_filename.clear();
}

void Request::run()
{
    socket = new QTcpSocket();
    if (!socket->setSocketDescriptor(socketDescriptor))
        return;
    connect(socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(onDisconnected()), Qt::DirectConnection);
    exec();
}

bool Request::getRequestHeader()
{
    QByteArray buffer = socket->readAll();
    QTextStream reader(buffer, QIODevice::ReadOnly);

    QStringList sec = reader.readLine().split(' ');
    if (sec.count() != 3)
        return false;

    request_header["_method"] = sec[0];
    request_header["_path"] = sec[1];
    request_header["_protocol"] = sec[2];

    while (!reader.atEnd())
    {
        QString line = reader.readLine();
        int pos = line.indexOf(':');
        if (pos == -1)
            continue;
        QString key = line.mid(0, pos).toLower();
        QString value = line.mid(pos + 2);
        request_header[key] = value;
    }

    //是否开启长连接支持
    if (s_keep_alive_enable)
    {

        if (request_header.contains("connection"))
        {
            //如果client发来的有长连接选项
            keep_alive = request_header["connection"].toLower() == "keep-alive";
            if (request_header["connection"].contains("keep-alive"))
            {
                keep_alive_timeout = s_keep_alive_timeout_max;
            }
        }
        else
        {
            keep_alive = s_keep_alive_default; //true
        }
    }

    return true;
}

void Request::tryResponseFile(QString filename)
{
    QFileInfo file_info(filename);

    if (file_info.isDir())
    {
        if (request_header["_path"].at(request_header["_path"].length() - 1) == '/')
        {
            if (s_index.size() != 0)
            {
                for (QStringList::Iterator i = s_index.begin(); i != s_index.end(); ++i)
                {
                    tryResponseFile(filename + *i);
                    if (response_code != 404)
                        return;
                }
                response_code = 404;
                return;
            }
            else
            {
                if (s_dir_listing)
                {
                    response_code = 200;//return the page successfully
                    response = new ResponseDirectory(socket, response_header, filename, request_header["_path"]);
                    return;
                }
                else
                {
                    response_code = 403; //server forbidden
                    return;
                }
            }
        }
        else
        {
            response_header["Location"] = "http://" + request_header["host"] + request_header["_path"] + '/';
            response_code = 301; //move to other space
            return;
        }
    }
    else if (file_info.exists())
    {
        if (file_info.isReadable())
        {
            if (request_header.contains("if-modified-since"))
            {
                if (request_header["if-modified-since"] == Common::getTimeStampString(file_info.lastModified().toUTC()))
                {
                    response_code = 304; //not modified
                    return;
                }
            }

            response_filename = filename;
            response_code = 200; //return the page successfully
            return;
        }
        else
        {
            response_code = 403;
            return;
        }
    }
    else
    {
        response_code = 404;
        return;
    }
}

void Request::onReadyRead()
{
    if (!getRequestHeader())
        return;
    keep_alive_timer.stop();

    if (s_keep_alive_enable && keep_alive)
    {
        response_header["Connection"] = "keep-alive"; //return to the browser
    }
    else
    {
        response_header["Connection"] = "close";
    }

    Log::instance()
                << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss") + ' '
                << '[' << socket->peerAddress().toString() << ']'
                << ' ' << request_header["_method"] << ' '
                << request_header["_path"] << ' ';

    tryResponseFile(s_root_path + request_header["_path"]);

    if (response == NULL)
    {
        response = new ResponseFile(socket, response_code, response_header, response_filename);
    }

    response->response();

    if (s_keep_alive_enable && keep_alive)
    {
        clearStatus();
        keep_alive_timer.setInterval(keep_alive_timeout);
        keep_alive_timer.start();
    }
    else
    {
        socket->close();
    }
}

void Request::onDisconnected()
{
    socket->deleteLater();
    quit();
}

void Request::onTimeout()
{
    qDebug() << "Connection timeout.";
    onDisconnected();
}
