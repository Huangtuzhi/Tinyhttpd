#include "common.h"
#include "request.h"
#include "settings.h"
#include "log.h"
#include "database.h"

#include "ui_monitorui.h"
#include "monitorui.h"

#include "starter.h"


MonitorUI::MonitorUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MonitorUI)
{
    ui->setupUi(this);
    setFixedSize( this->width (),this->height ()); // 禁止改变窗口大小。

    ui->label_blue->hide();
    ui->label_black->show();

    ports = Settings::instance().value("httpd/port").toString();
    ui->label_portv->setText(ports);

    QString ip = Starter::instance().getIPAddress();
    ui->label_ipv->setText(ip);
}

MonitorUI::~MonitorUI()
{
    delete ui;
}

void MonitorUI::on_pushButton_start_clicked()
{
    ui->label_blue->show();
    ui->label_black->hide();
    Log::instance() << APPLICATION_NAME << Log::NEWLINE << Log::FLUSH;
    if (!Starter::instance().start())
        return;
}

void MonitorUI::on_pushButton_stop_clicked()
{
    ui->label_blue->hide();
    ui->label_black->show();
    if (!Starter::instance().stop())
        return;
}
