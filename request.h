#ifndef REQUEST_H
#define REQUEST_H

#include "response.h"
#include "QThread"
#include <QTcpServer>
#include <QFile>
#include <QStringList>
#include <QTimer>

class Request: public QThread
{
    Q_OBJECT
public:
    Request(int socketDescriptor, QObject* parent = 0);
    virtual void run();

private:
    int socketDescriptor;
    QTcpSocket* socket;
    bool keep_alive;
    int keep_alive_timeout;
    QTimer* keep_alive_timer;
    QMap<QString, QString> request_header, response_header;
    int response_code;
    QString response_filename;
    Response* response;

    static bool s_initialized;
    static QString s_root_path;
    static QStringList s_index;
    static bool s_dir_listing;
    static bool s_keep_alive_enable;
    static bool s_keep_alive_default;
    static int s_keep_alive_timeout;
    static int s_keep_alive_timeout_max;

    void clearStatus();
    bool getRequestHeader();
    void tryResponseFile(QString filename);

    static void initialize();

public slots:
    void onReadyRead();
    void onDisconnected();
    void onTimeout();
};
#endif // REQUEST_H

