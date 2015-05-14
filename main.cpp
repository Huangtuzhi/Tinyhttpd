#include "monitorui.h"
#include "ui_monitorui.h"
#include <QApplication>
#include <QDir>
#include <QVariantList>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    QDir::setCurrent(QApplication::applicationDirPath());
    MonitorUI ui;
    ui.show();
    return a.exec();
}
