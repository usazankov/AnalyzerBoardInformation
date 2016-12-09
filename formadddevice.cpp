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
    QIcon icon;
    icon.addFile(QStringLiteral(":/images/ok.png"), QSize(),QIcon::Normal, QIcon::Off);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setIcon(icon);
    QIcon icon2;
    icon2.addFile(QStringLiteral(":/images/cancel.png"), QSize(),QIcon::Normal, QIcon::Off);
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setIcon(icon2);
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

dev::TypeBoard FormAddDevice::typeDev()
{
    switch (ui->comboTypeDev->currentIndex()) {
    case 0:
        return dev::ArincPCI429;
        break;
    case 1:
        return dev::ArincMPC429;
    default:
        return dev::ArincPCI429;
        break;
    }
}

int FormAddDevice::numberChannel()
{
    return ui->comboNumberChannel->currentText().toInt();
}

void FormAddDevice::on_comboTypeDev_activated(int index)
{
    QString temp;
    ArincBoardInterface *board;
    switch (index) {
    case 0:
        temp="dev/pci429_"+ui->comboIndexDev->currentText();
        ui->lineEdit->setText("Входной канал PCI429: "+QString::number(ArincChannelPCI429::count+1));
        board=new ArincBoardlPCI429(temp,0);
        break;
    case 1:
        temp="dev/mpc429_"+ui->comboIndexDev->currentText();
        ui->lineEdit->setText("Входной канал MPC429: "+QString::number(ArincChannelMPC429::count+1));
        board=new ArincBoardMPC429(temp,0);
        //MPC429;
        break;
    default:
        break;
    }
    if(board->BoardIsValid()){
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
        namedev=temp;
    }
    else ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    ui->statusDev->setText(board->getStatusBoard());
    ui->descriptionDev->setText(board->getDescriptionBoard());
    delete board;
}

void FormAddDevice::on_comboIndexDev_activated(int index)
{
    QString temp;
    ArincBoardInterface *board;
    switch (index) {
    case 0:
        temp="dev/pci429_"+QString::number(index);
        ui->lineEdit->setText("Входной канал PCI429: "+QString::number(ArincChannelPCI429::count+1));
        board=new ArincBoardlPCI429(temp,0);
        break;
    case 1:
        ui->lineEdit->setText("Входной канал MPC429: "+QString::number(ArincChannelMPC429::count+1));
        board=new ArincBoardMPC429(temp,0);
        //MPC429;
        break;
    default:
        break;
    }
        if(board->BoardIsValid()){
            ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
            namedev=temp;
        }else ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
        ui->statusDev->setText(board->getStatusBoard());
        ui->descriptionDev->setText(board->getDescriptionBoard());

    delete board;
}

void FormAddDevice::on_comboNumberChannel_activated(int index)
{

}
