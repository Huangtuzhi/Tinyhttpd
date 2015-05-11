#ifndef LOG
#define LOG

#include "common.h"
#include <sstream>
#include <QThreadStorage>

class Log
{

public:
    enum ctrl_t {FLUSH, NEWLINE};
    virtual ~Log();
    Log & operator << (QString str);
    Log & operator << (const char* str);
    Log & operator << (const char chr);
    Log & operator << (int num);
    Log & operator << (ctrl_t code);

    static Log & instance();
private:
    Log();
    static Log * m_instance;

    QThreadStorage<std::ostringstream*> buffer;
    bool log_file; //is open?
    bool show_log; //open or not?
};

#endif // LOG

