#include "server.h"
#include <QThread>
#include <QHostAddress>

class ServerThread: public QThread
{
    Q_OBJECT
public:
    explicit ServerThread(QObject *parent=0);
    virtual ~ServerThread();
    virtual void run();

    void setPort(int port);
    void setAddress(QHostAddress address);
private:
    Server* server;
    int m_port;
    QHostAddress m_address;
signals:

public slots:
};

