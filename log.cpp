#include "log.h"
#include "settings.h"
#include <iostream>
#include <fstream>
#include <QMutex>

QMutex mutex;
std::ofstream flog;

Log* Log::m_instance = NULL;

Log& Log::instance()
{
    if (m_instance == NULL)
        m_instance = new Log();
    return *m_instance;
}

Log::Log()
{
    show_log = Settings::instance().value("httpd/show_log", true).toBool();
    QString filename = Settings::instance().value("httpd/logfile", DEFAULT_HTTPD_LOGFILE).toString();

    if (filename != "")
    {
        flog.open(filename.toUtf8().data(), std::ios_base::app); //append mode
        log_file = flog.is_open();
    }
    else
        log_file = false;
}

Log::~Log()
{
    if (buffer.hasLocalData())
    {
        mutex.lock();
        if (show_log)
        {
            std::cout << buffer.localData()->str();
            std::cout.flush();
        }
        if (log_file)
        {
            flog << buffer.localData()->str();
            flog.close();
        }
        mutex.unlock();
        delete buffer.localData();
    }
}

Log &  Log::operator << (QString str)
{
    if (!buffer.hasLocalData())
        buffer.setLocalData(new std::ostringstream);
    *buffer.localData() << str.toUtf8().data();
    return *this;
}

Log & Log::operator << (int num)
{
    if (!buffer.hasLocalData())
        buffer.setLocalData(new std::ostringstream);
    * buffer.localData() << num;
    return *this;
}

Log & Log::operator << (const char * str)
{
    if (!buffer.hasLocalData())
        buffer.setLocalData(new std::ostringstream);
    * buffer.localData() << str;
    return *this;
}

Log & Log::operator << (const char chr)
{
    if (!buffer.hasLocalData())
        buffer.setLocalData(new std::ostringstream);
    * buffer.localData() << chr;
    return *this;
}

Log & Log::operator << (ctrl_t code)
{
    if (!buffer.hasLocalData())
        buffer.setLocalData(new std::ostringstream);
    mutex.lock();
    if (code == FLUSH)
    {
        if (show_log)
        {
            std::cout << buffer.localData()->str();
            std::cout.flush();
        }
        if (log_file)
        {
            flog << buffer.localData()->str();
            flog.flush();
        }
        buffer.localData()->clear();
    }
    else if (code == NEWLINE)
    {
        * buffer.localData() << '\n';
    }
    mutex.unlock();
    return *this;
}
