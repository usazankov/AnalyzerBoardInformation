#include "mdiform.h"
#include "ui_mdiform.h"

mdiForm::mdiForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mdiForm)
{
    ui->setupUi(this);
}

mdiForm::~mdiForm()
{
    delete ui;
}
