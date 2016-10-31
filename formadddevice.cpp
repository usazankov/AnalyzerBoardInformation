#include "formadddevice.h"
#include "ui_formadddevice.h"

FormAddDevice::FormAddDevice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FormAddDevice)
{
    ui->setupUi(this);
    devOk=0;
    ui->lineEdit->setText("Входной канал PCI429: "+QString::number(ArincChannelPCI429::count+1));
    ui->comboTypeDev->activated(ui->comboTypeDev->currentIndex());
}

FormAddDevice::~FormAddDevice()
{
    std::cout<<"FormAddDevice deleted"<<std::endl;
    delete ui;
}

QString FormAddDevice::nameChannel()
{
    return ui->lineEdit->text();
}

QString FormAddDevice::nameDevice()
{

    return namedev;
}

int FormAddDevice::numberChannel()
{
    return ui->comboNumberChannel->currentText().toInt();
}

void FormAddDevice::on_comboTypeDev_activated(int index)
{
    QString temp;
    switch (index) {
    case 0:
        temp="dev/pci429_"+ui->comboIndexDev->currentText();
        ui->lineEdit->setText("Входной канал PCI429: "+QString::number(ArincChannelPCI429::count+1));
        if(ArincBoardlPCI429::BoardIsValid(temp.toStdString().c_str())){
            ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
            namedev=temp;
        }
        else ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
        ui->statusDev->setText(ArincBoardlPCI429::getStatusBoard(temp.toStdString().c_str()));
        ui->descriptionDev->setText(ArincBoardlPCI429::getDescriptionBoard(temp.toStdString().c_str()));
        break;
    case 1:
        ui->lineEdit->setText("Входной канал MPC429: "+QString::number(ArincChannelMPC429::count+1));
        //MPC429;
        break;
    default:
        break;
    }
}

void FormAddDevice::on_comboIndexDev_activated(int index)
{
    QString temp;
    if(ui->comboTypeDev->currentIndex()==0){
        temp=QString("dev/pci429_")+QString::number(index);
        if(ArincBoardlPCI429::BoardIsValid(temp.toStdString().c_str())){
            ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
            namedev=temp;
        }else ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
        ui->statusDev->setText(ArincBoardlPCI429::getStatusBoard(temp.toStdString().c_str()));
        ui->descriptionDev->setText(ArincBoardlPCI429::getDescriptionBoard(temp.toStdString().c_str()));
    }
    else if(ui->comboTypeDev->currentIndex()==1){
        temp=QString("dev/mpc429_")+QString::number(index);
    }
}

void FormAddDevice::on_comboNumberChannel_activated(int index)
{

}
