#ifndef SERVICEUI_H
#define SERVICEUI_H
#include <QWidget>

namespace Ui {
class ServiceUI;
}

class ServiceUI: public QWidget
{
    Q_OBJECT

public:
    explicit ServiceUI(QWidget *parent = 0);
    ~ServiceUI();

private:
    Ui::ServiceUI *ui;
};


#endif // SERVICEUI_H
