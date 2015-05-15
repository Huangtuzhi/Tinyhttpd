#include "common.h"
#include "request.h"
#include "settings.h"
#include "log.h"
#include "database.h"
#include "starter.h"

#include "ui_monitorui.h"
#include "monitorui.h"

#include "ips.h"
#include "ui_ips.h"


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

    canvas = new ips();
}

MonitorUI::~MonitorUI()
{
    delete ui;
    delete canvas;
}

void MonitorUI::on_pushButton_start_clicked()
{
    ui->pushButton_start->setDisabled(true);
    ui->label_blue->show();
    ui->label_black->hide();
    Log::instance() << APPLICATION_NAME << Log::NEWLINE << Log::FLUSH;
    if (!Starter::instance().start()) //a Singleton Pattern instance
        return;
}

void MonitorUI::on_pushButton_stop_clicked()
{
    ui->label_blue->hide();
    ui->label_black->show();
    canvas->close();
    if (!Starter::instance().stop())
        return;
}

void MonitorUI::on_pushButton_all_clicked(bool checked)
{
    if (checked)
    {
        canvas->getData();
        canvas->show();
    }
    else
        canvas->hide();
}

