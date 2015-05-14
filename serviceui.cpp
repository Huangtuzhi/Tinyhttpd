#include "serviceui.h"
#include "ui_serviceui.h"

ServiceUI::ServiceUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServiceUI)
{
    ui->setupUi(this);
}

ServiceUI::~ServiceUI()
{
    delete ui;
}
