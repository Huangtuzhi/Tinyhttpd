#include "server.h"
#include "request.h"

Server::Server(QObject* parent): QTcpServer(parent)
{
}

bool Server::start(QHostAddress address, int port)
{
    return listen(address, port);
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    Request* request = new Request(socketDescriptor); //Constructor(timer.start) in old thread
    request->start();
}
