#include "mdiformdiscr.h"
#include "ui_mdiformdiscr.h"

MdiFormDiscr::MdiFormDiscr(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MdiFormDiscr)
{
    ui->setupUi(this);
}

MdiFormDiscr::~MdiFormDiscr()
{
    delete ui;
}
