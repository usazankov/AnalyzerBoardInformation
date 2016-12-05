#include "formdiscrparam.h"
#include "ui_formdiscrparam.h"

FormDiscrParam::FormDiscrParam(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormDiscrParam)
{
    ui->setupUi(this);
}

FormDiscrParam::~FormDiscrParam()
{
    delete ui;
}
