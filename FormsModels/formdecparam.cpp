#include "formdecparam.h"
#include "ui_formdecparam.h"

FormDecParam::FormDecParam(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormDecParam)
{
    ui->setupUi(this);
}

void FormDecParam::setUnpackConst(double uc)
{
    ui->doubleSpinBox->setValue(uc);
}

double FormDecParam::UnpackConst()
{
    return ui->doubleSpinBox->value();
}

void FormDecParam::setLeastBit(int bit)
{
    ui->spinBox_2->setValue(bit);
}

int FormDecParam::leastBit()
{
    return ui->spinBox_2->value();
}

void FormDecParam::setMostBit(int bit)
{
    ui->spinBox->setValue(bit);
}

int FormDecParam::mostBit()
{
    return ui->spinBox->value();
}

FormDecParam::~FormDecParam()
{
    delete ui;
}

void FormDecParam::on_doubleSpinBox_valueChanged(double arg1)
{
    emit changeUnpackConst(arg1);
}

void FormDecParam::on_spinBox_valueChanged(int arg1)
{
    emit changeMostBit(arg1);
}

void FormDecParam::on_spinBox_2_valueChanged(int arg1)
{
    emit changeLeastBit(arg1);
}
