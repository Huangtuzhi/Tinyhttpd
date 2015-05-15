#include "database.h"
#include <iostream>
#include <sstream>

Database::Database(int port, std::string ip): m_ip(ip), m_port(port)
{
    context = redisConnect(m_ip.data(), m_port);
    if (context!=NULL && context->err)
        std::cout << "Error: %s\n" << context->errstr;
    else
        std::cout << "Database connected\n";
}


void Database::recordIP(int vistor, std::string time, std::string ip, int port, std::string agent)
{
    std::stringstream ss;
    std::string vistor_s;
    ss << vistor;
    ss >> vistor_s;
    std::string _vistor = std::string("vistor:") + vistor_s;
    std::cout << _vistor.data() << std::endl;

    reply = (redisReply*)redisCommand(context, "HMSET %s time %s ip %s port %d agent %s", _vistor.data(), time.data(), ip.data(), port, agent.data());
    std::cout << "ERROE INFO: " << reply->str << std::endl;
    freeReplyObject(reply);
}

std::string Database::readIP(int vistor)
{
    std::stringstream ss;
    std::string vistor_s;
    ss << vistor;
    ss >> vistor_s;
    std::string _vistor = std::string("vistor:") + vistor_s;

    std::string buffer;
    reply = (redisReply*)redisCommand(context, "HMGET %s time ip port", _vistor.data());
    if (reply->type == REDIS_REPLY_ARRAY) {
        if(reply->element[0]->str == NULL)
            return "";

        for (unsigned int j = 0; j < reply->elements; j++) {
            buffer += std::string(reply->element[j]->str) + " ";
        }
    }
    return buffer;
}

Database::~Database()
{
    redisFree(context);
    std::cout << "~Database() Called" << std::endl;
}
