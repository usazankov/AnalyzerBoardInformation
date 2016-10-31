#include "formconfparamsdevice.h"
#include "ui_formconfparamsdevice.h"

FormConfParamsDevice::FormConfParamsDevice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FormConfParamsDevice)
{
    ui->setupUi(this);
}

FormConfParamsDevice::~FormConfParamsDevice()
{
    delete ui;
}
