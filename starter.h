#ifndef START
#define START
#include "common.h"
#include "request.h"
#include "settings.h"
#include "log.h"
#include "database.h"
#include "iostream"

#include "serverthread.h"

class Starter
{
public:
    static Starter& instance();
    void startInstance(int port);
    bool start();
    bool stop();
    QString getIPAddress();

private:
    static Starter* m_instance;
    std::vector<ServerThread*> threads;
};

#endif // START

