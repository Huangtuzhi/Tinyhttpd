#include "common.h"
#include "serverthread.h"
#include "request.h"
#include "settings.h"
#include "log.h"
#include "database.h"
#include <QtCore/QCoreApplication>
#include <QDir>
#include <QVariantList>

void startInstance(int port)
{
    ServerThread* server_thread = new ServerThread();
    server_thread->setAddress(QHostAddress::Any);
    server_thread->setPort(port);
    server_thread->start();
}

bool start()
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

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);
    QDir::setCurrent(QCoreApplication::applicationDirPath());

    Log::instance() << APPLICATION_NAME << Log::NEWLINE << Log::FLUSH;

    if (!start())
        return -1;

//    Database redis(6378);
//    redis.recordIP("202.201.1.1", 80, "2015-5-13 10:40");
    return a.exec();
}
