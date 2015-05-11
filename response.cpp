#include "response.h"
#include "httpstatus.h"
#include "log.h"
#include <QDateTime>

Response::Response(QTcpSocket* socket, int http_status_code, QMap<QString, QString>& header):
    m_socket(socket),
    m_http_status_code(http_status_code),
    m_header(header)
{
    m_header["Server"] = APPLICATION_IDENTIFIER;
    m_header["Date"] = Common::getTimeStampString();
}

void Response::responseHeader()
{
    m_socket->write("HTTP/1.0 ");

    switch (m_http_status_code)
    {
    case 200:
        m_socket->write(HTTP_STATUS_200);
        Log::instance() << HTTP_STATUS_200 << Log::NEWLINE << Log::FLUSH;
        break;
    case 301:
        m_socket->write(HTTP_STATUS_301);
        Log::instance() << HTTP_STATUS_301 << Log::NEWLINE << Log::FLUSH;
        break;
    case 304:
        m_socket->write(HTTP_STATUS_304);
        Log::instance() << HTTP_STATUS_304 << Log::NEWLINE << Log::FLUSH;
        break;
    case 403:
        m_socket->write(HTTP_STATUS_403);
        Log::instance() << HTTP_STATUS_403 << Log::NEWLINE << Log::FLUSH;
        break;
    case 404:
        m_socket->write(HTTP_STATUS_404);
        Log::instance() << HTTP_STATUS_404 << Log::NEWLINE << Log::FLUSH;
        break;
    default:
        m_socket->write(QString("%1").arg(m_http_status_code).toLatin1());
    }

    m_socket->write("\r\n");

    QMap<QString, QString>::iterator i;
    for(i = m_header.begin(); i != m_header.end(); ++i)
    {
        m_socket->write(i.key().toLatin1());
        m_socket->write(": ");
        m_socket->write(i.value().toLatin1());
        m_socket->write("\r\n");
    }
    m_socket->write("\r\n");
}

