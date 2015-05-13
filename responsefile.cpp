#include "responsefile.h"
#include "mime.h"
#include <QFile>
#include <QFileInfo>

bool ResponseFile::s_initialized = false;
int ResponseFile::s_buffer_size = DEFAULT_REQUEST_BUFFER_SIZE;
int ResponseFile::vistor = 0;

void ResponseFile::initialize()
{
    s_initialized = true;
    s_buffer_size = 1048576;
}

//return the page in server
ResponseFile::ResponseFile(QTcpSocket* socket, int http_status_code, QMap<QString, QString>& header, QString filename):
    Response(socket, http_status_code, header),
    m_filename(filename)
{
    if (!s_initialized)
        initialize();
    if (m_http_status_code != 200)
    {
        m_filename = QString("response/%1.html").arg(m_http_status_code);
    }
    QFileInfo file_info(m_filename);
    m_header["Content-Type"] = Mime::instance().getMimeType(file_info.suffix());
    m_header["Content-Length"] = QString("%1").arg(file_info.size());
    m_header["Last-Modified"] = Common::getTimeStampString(file_info.lastModified().toUTC());
}

void ResponseFile::response()
{
    responseHeader();

    QFile file(m_filename);
    if (!file.open(QFile::ReadOnly))
        ; //TODO
    char* buffer =  new char[s_buffer_size];
    while (!file.atEnd())
    {
        int len = file.read(buffer, s_buffer_size);
        m_socket->write(buffer, len);
        m_socket->flush();
    }
    delete[] buffer;
    incrVistor();
}

