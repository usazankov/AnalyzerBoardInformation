#include "mdigrafform.h"
#include "ui_mdigrafform.h"
int MdiGrafForm::timeStepToUpdate=Ui::DefaultTimeStepToUpdateGrafiks;
MdiGrafForm::MdiGrafForm(QString title, int index, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MdiGrafForm)
{
    ui->setupUi(this);
    this->setWindowTitle(title);
    this->i=index;
    count_Observers=0;
    runningPlot=0;
    model=Q_NULLPTR;
}

ArincGrafikPanel *MdiGrafForm::graphPanel(int adress)
{
    return grafiks[adress];
}

QMap<int, ArincGrafikPanel *> *MdiGrafForm::arincGrafikPanels()
{
    return &grafiks;
}

int MdiGrafForm::index() const
{
    return i;
}

void MdiGrafForm::addGrafik(int adress)
{
    cout<<"ADD Grafik"<<endl;
    if(!grafiks.contains(adress)){
        ArincGrafikPanel *grafik=new ArincGrafikPanel(adress,this);
        grafik->setTimeStepToReplot(MdiGrafForm::timeStepToUpdate);
        model->registerObserver(grafik);
        ++count_Observers;
        connect(this,SIGNAL(signalToStartPlotting(int)),grafik,SLOT(start(int)));
        connect(this,SIGNAL(signalToStopPlotting()),grafik,SLOT(stop()));
        connect(this,SIGNAL(setTimeStepToUpdate(int)),grafik,SLOT(setTimeStepToReplot(int)));
        ui->verticalLayout->addWidget(grafik);
        grafiks[adress]=grafik;
    }
}

void MdiGrafForm::delObservers()
{
    cout<<"count_Observers del before: "<<count_Observers<<endl;
    emit stopPlotting();
    foreach (ArincGrafikPanel* p, grafiks) {
        if(count_Observers>0){
            if(model!=Q_NULLPTR)
                model->removeObserver(p);
            p->stop();
            --count_Observers;
        }
    }
   cout<<"count_Observers del after: "<<count_Observers<<endl;
}

void MdiGrafForm::addObservers()
{
    cout<<"count_Observers before: "<<count_Observers<<endl;
    foreach (ArincGrafikPanel* p, grafiks) {
        if(model!=Q_NULLPTR)
            model->registerObserver(p);
        ++count_Observers;
    }
    emit startPlotting();
    cout<<"count_Observers after: "<<count_Observers<<endl;
}

void MdiGrafForm::setModel(ArincModelInterface *model)
{
    this->model=model;
}

void MdiGrafForm::clearDataGrafiks()
{
    foreach (ArincGrafikPanel* p, grafiks) {
        p->clearData();
    }
}

int MdiGrafForm::countObservers()
{
    return count_Observers;
}

void MdiGrafForm::startPlotting()
{
    if(model!=Q_NULLPTR)
        if(count_Observers>0&&model->isRunningArinc()){
            emit signalToStartPlotting(MdiGrafForm::timeStepToUpdate);
            runningPlot=1;
        }
}

void MdiGrafForm::stopPlotting()
{
    if(model!=Q_NULLPTR)
        if(count_Observers>0&&model->isRunningArinc()){
            emit signalToStopPlotting();
            runningPlot=0;
        }
}


void MdiGrafForm::setDefaultTimeStepToUpdate(int timeStep)
{
    MdiGrafForm::timeStepToUpdate=timeStep;
}

bool MdiGrafForm::isRunningPlot() const
{
    return runningPlot;
}

MdiGrafForm::~MdiGrafForm()
{
    emit deletedGrafForm(index());
    foreach (ArincGrafikPanel* grafik, grafiks) {
        if(count_Observers>0){
            if(model!=Q_NULLPTR){
                model->removeObserver(grafik);
                --count_Observers;
            }
        }
        disconnect(this,SIGNAL(signalToStartPlotting(int)),grafik,SLOT(start(int)));
        disconnect(this,SIGNAL(signalToStopPlotting()),grafik,SLOT(stop()));
        delete grafik;
        grafiks.remove(grafiks.key(grafik));
    }
    delete ui;
}

void MdiGrafForm::resetModel()
{
    model=Q_NULLPTR;
}


