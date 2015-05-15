#include "ips.h"
#include "ui_ips.h"
#include "monitorui.h"
#include "ui_monitorui.h"
#include <iostream>
#include <log.h>

ips::ips(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ips)
{
    ui->setupUi(this);
    this->setFixedSize( this->width (),this->height ()); // 禁止改变窗口大小。
    this->setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
}

ips::~ips()
{
    delete ui;
}

void ips::getData()
{
    std::string buffer, text;
    redis = new Database(6378);
    int index = 1;

    buffer = redis->readIP(index);
    while (buffer != std::string(""))
    {
        buffer = redis->readIP(++index);
        text = text + "\n" + buffer;
    }
    ui->info->setText(text.data());
}

