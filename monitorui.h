#ifndef MONITORUI_H
#define MONITORUI_H

#include <QMainWindow>
#include <ips.h>

namespace Ui {
class MonitorUI;
}

class MonitorUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit MonitorUI(QWidget *parent = 0);
    ~MonitorUI();

private slots:
    void on_pushButton_start_clicked();
    void on_pushButton_stop_clicked();
    void on_pushButton_all_clicked(bool checked);

private:
    Ui::MonitorUI *ui;
    QString ports;
    ips *canvas;
};

#endif // MONITORUI_H
