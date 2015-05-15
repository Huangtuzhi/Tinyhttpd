#ifndef DATABASE
#define DATABASE
#include <hiredis/hiredis.h>
#include <string>

class Database
{
public:
    Database(int port, std::string ip="127.0.0.1");
    ~Database();
    void recordIP(int vistor, std::string time, std::string ip, int port, std::string agent);
    std::string readIP(int vistor);

private:
    std::string m_ip;
    int m_port;
    redisContext* context;
    redisReply* reply;
};

#endif

