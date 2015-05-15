#include "starter.h"
#include <vector>
#include <iostream>
#include <QNetworkInterface>
#include <QStringList>
#include <QHostAddress>

Starter* Starter::m_instance = NULL;

Starter& Starter::instance()
{
    if (m_instance == NULL)
        m_instance = new Starter();
    return *m_instance;
}

void Starter::startInstance(int port)
{
    ServerThread* server_thread = new ServerThread();
    threads.push_back(server_thread);
    server_thread->setAddress(QHostAddress::Any);
    server_thread->setPort(port);
    server_thread->start();
}

bool Starter::start()
{
    //监听多端口，每个端口都启动服务器进程
    bool ok;
    QString t_port = Settings::instance().value("httpd/port").toString();
    QStringList port_list = t_port.split("|");

    //多线程监听
    for(int i = 0; i < port_list.size(); i++)
    {
        int port = port_list[i].toInt(&ok,10);
        startInstance(port);
    }
    return true;
}

bool Starter::stop()
{
    for(auto t:threads)
    {
        t->exit();
        t->wait();
    }
    return true;
}

QString Starter::getIPAddress()
{
    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address()) {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    return ipAddress;
}
