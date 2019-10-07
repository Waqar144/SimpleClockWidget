#include "prefrences.h"
#include "ui_prefrences.h"

#include<QSettings>
#include<QDebug>
#include<QColorDialog>

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
    int opacity = static_cast<int>(settings.value("Opacity").toReal() * 100);
    qDebug()<<opacity;
    ui->opacitySlider->setValue(opacity);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &prefrences::onAccepted);
    connect(ui->colorSelect, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this, &prefrences::colorChanged);
    connect(ui->opacitySlider, &QSlider::valueChanged, this, &prefrences::opacityValueChanged);
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
    qreal opacity = static_cast<qreal>(ui->opacitySlider->value());
    opacity /= 100;
    qDebug()<<"onAccepted(): "<<opacity;
    settings.setValue("Opacity", opacity);
}

void prefrences::on_fontSizeSpinBox_valueChanged(int arg1)
{
    emit fontValueChanged(arg1);
}

void prefrences::on_fontComboBox_currentFontChanged(const QFont &f)
{
    emit fontChanged(f);
}
