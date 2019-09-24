#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(clock);

    QApplication a(argc, argv);

    a.setOrganizationName(QString("Code Buffer"));
    a.setApplicationName("Clock Widget");

    MainWindow w;
    w.show();
    return a.exec();
}
