#ifndef PREFRENCES_H
#define PREFRENCES_H

#include <QDialog>

namespace Ui {
class prefrences;
}

class prefrences : public QDialog
{
    Q_OBJECT

public:
    explicit prefrences(QWidget *parent = nullptr);
    ~prefrences();

signals:
    void fontValueChanged(int size);
    void fontChanged(const QFont &f);
    void colorChanged(int color);
    void opacityValueChanged(int opacity);

private:
    Ui::prefrences *ui;

    void loadSettings();

private slots:
    void onAccepted();
};

#endif // PREFRENCES_H
