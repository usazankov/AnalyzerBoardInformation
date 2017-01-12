#include "mdigrafform.h"
#include "ui_mdigrafform.h"

MdiGrafForm::MdiGrafForm(QString title, int index, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MdiGrafForm)
{
    ui->setupUi(this);
    this->setWindowTitle(title);
    this->index=index;
}

ArincGrafikPanel *MdiGrafForm::graphPanel(int adress)
{
    return grafiks[adress];
}

void MdiGrafForm::addGrafik(int adress)
{
    cout<<"ADD Grafik"<<endl;
    if(!grafiks.contains(adress)){
        ArincGrafikPanel *grafik=new ArincGrafikPanel(adress,this);
        model->registerObserver(grafik);
        ui->verticalLayout->addWidget(grafik);
        grafiks[adress]=grafik;
    }
}

void MdiGrafForm::setModel(ArincModelInterface *model)
{
    this->model=model;
}

MdiGrafForm::~MdiGrafForm()
{
    foreach (ArincGrafikPanel* grafik, grafiks) {
        delete grafik;
        grafiks.remove(grafiks.key(grafik));
    }
    emit deletedGrafForm(index);
    delete ui;
}


