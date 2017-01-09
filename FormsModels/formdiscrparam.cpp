#include "formdiscrparam.h"
#include "ui_formdiscrparam.h"

FormDiscrParam::FormDiscrParam(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormDiscrParam)
{
    ui->setupUi(this);
}

QTableView *FormDiscrParam::TableView()
{
    return ui->tableView;
}

QPushButton *FormDiscrParam::ButtonAdd()
{
    return ui->pushButton_2;
}

QPushButton *FormDiscrParam::ButtonDel()
{
    return ui->pushButton;
}

FormDiscrParam::~FormDiscrParam()
{
    delete ui;
}

