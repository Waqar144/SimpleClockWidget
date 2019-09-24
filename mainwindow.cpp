#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "prefrences.h"

#include<QTimer>
#include<QTime>
#include<QPoint>
#include<QMouseEvent>
#include<QMenu>
#include<QSettings>

#include<QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //load settings
    QSettings settings;
    restoreGeometry(settings.value("MainGeometry").toByteArray());
    restoreState(settings.value("MainState").toByteArray());

    //this->setFixedSize(400, 100);
    //make the background transparent
    setAttribute(Qt::WA_TranslucentBackground);
    //make it stay on top and remove all window borders
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::Tool);

    //connection for our custom context menu
    connect(this, &MainWindow::customContextMenuRequested,
            this, &MainWindow::showContextMenu);

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
    QDateTime dt = QDateTime::currentDateTime();
    QTime currentTime = dt.time();
    QString currentTimeString = currentTime.toString("hh:mm ap");

   // qDebug() << currentTime.toString("hh:mm ap");
    if(currentTime.second() %2 == 0)
        currentTimeString[2] = ' ';

    ui->lcdNumber->display(currentTimeString);
    setColour();
}

void MainWindow::showContextMenu(const QPoint &pos)
{
    QMenu contextMenu;
    contextMenu.addAction(QString("Quit"), this, SLOT(close()));
    contextMenu.addAction(QString("Preferences"), this, SLOT(showPreferences()));
    contextMenu.exec(mapToGlobal(pos));
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton) {
        emit customContextMenuRequested(event->pos());
    } else {
      QMainWindow::mouseReleaseEvent(event);
    }
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    m_mousePos = e->pos();
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    move(e->globalPos() - m_mousePos);
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    QSettings settings;
    settings.setValue("MainGeometry", saveGeometry());
    settings.setValue("MainState", saveState());
    e->accept();
}

void MainWindow::setColour()
{
    QSettings settings;
    int colour = settings.value("Colour").toInt();
    QPalette p;
    QColor color;

    switch (colour) {
        case 0:
            p.setColor(QPalette::Foreground, Qt::black);
            break;
        case 1:
            p.setColor(QPalette::Foreground, Qt::red);
            break;
        case 2:
            p.setColor(QPalette::Foreground, Qt::blue);
            break;
        case 3:
            p.setColor(QPalette::Foreground, Qt::green);
            break;
        case 4:
            p.setColor(QPalette::Foreground, Qt::yellow);
            break;
        case 5:
            color = QColor::fromRgb(62, 0, 174);
            p.setColor(QPalette::Foreground, color);
            break;
    }
    this->ui->lcdNumber->setPalette(p);
    this->update();
}

void MainWindow::showPreferences()
{
    prefrences p(this);
    p.exec();
    setColour();
}
