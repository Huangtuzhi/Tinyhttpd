#ifndef IPS_H
#define IPS_H

#include <QWidget>
#include <database.h>

namespace Ui {
class ips;
}

class ips : public QWidget
{
    Q_OBJECT

public:
    explicit ips(QWidget *parent = 0);
    void getData();
    ~ips();

private:
    Ui::ips* ui;
    Database* redis;
};

#endif // IPS_H
