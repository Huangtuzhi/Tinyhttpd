#ifndef SERVER
#define SERVER

#include <QTcpServer>

class Server: public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QObject* parent = 0);
    bool start(QHostAddress address, int port);

    //the parameter changed
protected:
    void incomingConnection(qintptr socketDescriptor);
};

#endif

