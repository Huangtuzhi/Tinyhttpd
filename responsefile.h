#ifndef RESPONSEFILE
#define RESPONSEFILE

#include "common.h"
#include "response.h"

class ResponseFile: public Response
{
public:
    ResponseFile(QTcpSocket* socket, int http_status_code, QMap<QString, QString>& header, QString filename);
    virtual void response();

protected:
    QString m_filename;

private:
    static void initialize();

    static bool s_initialized;
    static int s_buffer_size;
};


#endif // RESPONSEFILE

