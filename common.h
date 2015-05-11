#ifndef COMMON
#define COMMON

#include <QDebug>
#include <QString>
#include <QDateTime>

const QString APPLICATION_NAME = "TinyHttpServer";
const QString APPLICATION_VERSION = "0.0.1";
const QString APPLICATION_IDENTIFIER = APPLICATION_NAME + '/' + APPLICATION_VERSION;
const QString CONFIG_FILE = "tinyhttpd.ini";
const QString MIME_TYPE_FILE = "mime.txt";

const QString DEFAULT_HTTPD_LOGFILE = "tinyhttpd.log";
const int DEFAULT_REQUEST_BUFFER_SIZE = 65536;
const bool DEFAULT_REQUEST_KEEP_ALIVE_ENABLE = true;
const bool DEFAULT_REQUEST_KEEP_ALIVE_DEFAULT = true;
const int DEFAULT_REQUEST_KEEP_ALIVE_TIMEOUT = 30;
const int DEFAULT_REQUEST_KEEP_ALIVE_TIMEOUT_MAX = 300;
const bool DEFAULT_SITE_DIR_LISTING = false;

class Common
{
public:
    static QString getTimeStampString(QDateTime datetime = QDateTime::currentDateTimeUtc());
};

#endif // COMMON

