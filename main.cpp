#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setOrganizationName(QString("Code Buffer"));
    a.setApplicationName("Clock Widget");

    MainWindow w;
    w.show();
    return a.exec();
}
