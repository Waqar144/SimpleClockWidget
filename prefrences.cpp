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
    ui->colorSelect->setCurrentIndex(settings.value("Colour").toInt());
    ui->timeFormatSelect->setCurrentIndex(settings.value("TimeFormat").toInt());
    QFont font(settings.value("Font").toString());
    ui->fontComboBox->setCurrentFont(font);
    ui->fontSizeSpinBox->setValue(settings.value("FontSize").toInt());
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
    settings.setValue("Font", ui->fontComboBox->currentFont().toString());
    settings.setValue("FontSize", ui->fontSizeSpinBox->value());
}
