#include "serverthread.h"
#include "log.h"

ServerThread::ServerThread(QObject *parent):
    QThread(parent), m_port(8000), m_address(QHostAddress::AnyIPv6)
{
    connect(this, SIGNAL(finished()), this, SLOT(deleteLater()));
}

ServerThread::~ServerThread()
{
    delete server;
}

void ServerThread::run()
{
    server = new Server();
    if(!server->start(m_address, m_port))
    {
        Log::instance() << "Failed to listen port " << m_port << Log::NEWLINE << Log::FLUSH;
        quit();
    }
    Log::instance()<< "Listening " << m_address.toString() << ":" << m_port << Log::NEWLINE << Log::FLUSH;
    exec();
}

void ServerThread::setPort(int port)
{
    m_port = port;
}

void ServerThread::setAddress(QHostAddress address)
{
    m_address = address;
}
