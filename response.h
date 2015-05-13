#ifndef RESPONSE
#define RESPONSE

#include <common.h>
#include <QMap>
#include <QTcpSocket>

class Response
{
public:
    Response(QTcpSocket* socket, int http_status_code, QMap<QString, QString>& header);
    virtual void response() = 0;
    virtual int getVistor() = 0;
    virtual void incrVistor() = 0;

protected:
    void responseHeader();

    QTcpSocket* m_socket;
    int m_http_status_code;
    QMap<QString, QString> m_header;
};

#endif // RESPONSE

