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

    ui->centralwidget->layout()->setContentsMargins(0,0,0,0);
    this->layout()->setContentsMargins(0,0,0,0);
    this->layout()->setSizeConstraint(QLayout::SetMinimumSize);

    //load settings
    QSettings settings;
    restoreGeometry(settings.value("MainGeometry").toByteArray());
    restoreState(settings.value("MainState").toByteArray());

    //set Flags
    setWindowFlag(Qt::WindowStaysOnTopHint);
    setWindowFlag(Qt::Tool);
    setWindowFlag(Qt::FramelessWindowHint);
    //make window transparent
    setAttribute(Qt::WA_TranslucentBackground);

    createTrayMenu();
    updatePreferences();

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

void MainWindow::createTrayMenu()
{
    //add tray icon
    QIcon icon(":/icon.png");
    trayicon = new QSystemTrayIcon(this);
    trayicon->setIcon(icon);
    //tray icon menu
    trayIconMenu = new QMenu(this);
    //create the actions
    QAction *minimizeAction = new QAction(tr("Mi&nimize"), this);
    connect(minimizeAction, &QAction::triggered, this, &MainWindow::hide);
    QAction *showAction= new QAction(tr("&Show"), this);
    connect(showAction, &QAction::triggered, this, &MainWindow::show);
    QAction *quitAction= new QAction(tr("&Quit"), this);
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
    //add the actions to tray menu
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(showAction);
    trayIconMenu->addAction(quitAction);
    //add them to the tray
    trayicon->setContextMenu(trayIconMenu);
    trayicon->show();

}

void MainWindow::updateTime()
{
    QDateTime dt = QDateTime::currentDateTime();
    QTime currentTime = dt.time();
    QString currentTimeString;
    QSettings s;

    int timeformat = s.value("TimeFormat").toInt();
    if(timeformat == 0)
        currentTimeString = currentTime.toString("hh:mm AP");
    else
        currentTimeString = currentTime.toString("hh:mm");

   // qDebug() << currentTime.toString("hh:mm ap");
    if(currentTime.second() %2 == 0)
        currentTimeString[2] = ' ';

    ui->timeDisplay->setText(currentTimeString);
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
    //e->pos will return position of cursor relative to the current window
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
    qApp->quit();
}

void MainWindow::setColour(int colour)
{
    QPalette p = ui->timeDisplay->palette();
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
            color = QColor::fromRgb(62, 0, 174, 100);
            p.setColor(QPalette::Foreground, color);
            break;
        case 6:
            p.setColor(QPalette::Foreground, Qt::white);
    }
    this->ui->timeDisplay->setPalette(p);
    this->update();
}

void MainWindow::showPreferences()
{
    prefrences p(this);

    connect(&p, SIGNAL(fontValueChanged(int)), this, SLOT(changeFontSize(int)));
    connect(&p, SIGNAL(fontChanged(QFont)), this, SLOT(onFontChanged(QFont)));
    connect(&p, &prefrences::colorChanged, this, &MainWindow::onColorChanged);
    connect(&p, &prefrences::opacityValueChanged, this, &MainWindow::onOpacityChanged);

    p.exec();
    updatePreferences();
}

void MainWindow::changeFontSize(int size)
{
    qDebug() << "Recv Size: "<<size;
    QSettings settings;
    QFont font(settings.value("Font").toString());
    font.setPointSize(size);
    ui->timeDisplay->setFont(font);
}

void MainWindow::onFontChanged(QFont f)
{
    QSettings settings;
    f.setPointSize(settings.value("FontSize").toInt());
    ui->timeDisplay->setFont(f);
}

void MainWindow::onColorChanged(int color)
{
    setColour(color);
}

void MainWindow::onOpacityChanged(int opacity)
{
    qreal op = static_cast<qreal>(opacity);
    op = op/100;
    qDebug()<<opacity;
    qDebug()<<op;
    QPalette p = ui->timeDisplay->palette();
    QColor c = p.color(QPalette::Foreground);
    c.setAlphaF(op);
    p.setColor(QPalette::Foreground, c);
    ui->timeDisplay->setPalette(p);
    this->update();
}

void MainWindow::updatePreferences()
{
    QSettings settings;
    QFont font(settings.value("Font").toString());
    font.setPointSize(settings.value("FontSize").toInt());
    ui->timeDisplay->setFont(font);

    int colour = settings.value("Colour").toInt();
    setColour(colour);

    //qreal opac = settings.value("Opacity").toReal();
    int opacity = static_cast<int>(settings.value("Opacity").toReal() * 100);
    //int opacity = static_cast<int>(opac * 100);
    onOpacityChanged(opacity);

}
