#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QTimer>
#include<QTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateTime);
    timer->start(1000);

    updateTime();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateTime()
{
    QTime currentTime = QTime::currentTime();
    QString currentTimeString = currentTime.toString("hh:mm");
    if(currentTime.second() %2 == 0)
        currentTimeString[2] = ' ';

    ui->lcdNumber->display(currentTimeString);

}
