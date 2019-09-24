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

private:
    Ui::prefrences *ui;

private slots:
    void onAccepted();
};

#endif // PREFRENCES_H
