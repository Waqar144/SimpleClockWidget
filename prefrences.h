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

private:
    Ui::prefrences *ui;

private slots:
    void onAccepted();
    void on_fontSizeSpinBox_valueChanged(int arg1);
};

#endif // PREFRENCES_H
