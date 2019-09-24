#include "prefrences.h"
#include "ui_prefrences.h"

#include<QSettings>

prefrences::prefrences(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::prefrences)
{
    ui->setupUi(this);

    QSettings settings;

    //show all previous settings
    //set colour
    ui->colorSelect->setCurrentIndex(settings.value("Colour").toInt());
    //set time format
    ui->timeFormatSelect->setCurrentIndex(settings.value("TimeFormat").toInt());

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &prefrences::onAccepted);
}

prefrences::~prefrences()
{
    delete ui;
}

void prefrences::onAccepted()
{
    QSettings settings;
    settings.setValue("Colour", ui->colorSelect->currentIndex());
    settings.setValue("TimeFormat", ui->timeFormatSelect->currentIndex());
}
