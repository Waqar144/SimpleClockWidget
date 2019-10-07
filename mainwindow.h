#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updateTime();
    void showContextMenu(const QPoint&);
    void showPreferences();
    void changeFontSize(int size);
    void onFontChanged(QFont f);
    void onColorChanged(int);

protected:
    void mouseReleaseEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void closeEvent(QCloseEvent *);

private:
    Ui::MainWindow *ui;
    QPoint m_mousePos;

    QSystemTrayIcon *trayicon;
    QMenu* trayIconMenu;

    void createTrayMenu();
    void setColour(int colour);
    void updatePreferences();
};
#endif // MAINWINDOW_H
