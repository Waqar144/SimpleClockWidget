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
    void fontChanged(QFont f);
    void colorChanged(int color);

private:
    Ui::prefrences *ui;

private slots:
    void onAccepted();
    void on_fontSizeSpinBox_valueChanged(int arg1);
    void on_fontComboBox_currentFontChanged(const QFont &f);
};

#endif // PREFRENCES_H
