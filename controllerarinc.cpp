#include "controllerarinc.h"

ControllerArinc::ControllerArinc(MdiForm *form, ArincModelInterface *model)
{
    this->model=model;
    this->form=form;
    ArincReader *r=dynamic_cast<ArincReader*>(model);
    connect(r,SIGNAL(sendLogsData(QVector<TimeParametr>)),this,SLOT(buildGrafik(QVector<TimeParametr>)));
}

ControllerArinc::~ControllerArinc()
{
    cout<<"deleted Controller"<<endl;
}

void ControllerArinc::Start(int time_milliseconds)
{
    model->startArinc(time_milliseconds);
}

void ControllerArinc::Stop()
{
    model->stopArinc();
}

void ControllerArinc::addObserveredArincWord(int adress)
{
    if(!model->hasArincParametr(adress))
        model->addArincParametr(new ArincParametr(adress));
}

void ControllerArinc::addDiscrModel(int adress)
{
    if(!discrs_models.contains(adress)){
        discrs_models.push_back(adress);
    }
}

void ControllerArinc::deleteDiscrModel(int adress)
{
    discrs_models.removeOne(adress);
    form->deleteDiscrTable(adress);
}

void ControllerArinc::setTitleForm(const QString &name)
{
    form->setWindowTitle(name);
}

void ControllerArinc::deleteAllDiscrModel()
{
    while(!discrs_models.empty()){
        deleteDiscrModel(discrs_models.back());
    }

}

QString ControllerArinc::TitleForm() const
{
    return form->windowTitle();
}

MdiForm *ControllerArinc::getMdiForm()
{
    return form;
}

void ControllerArinc::setNameArincParametr(const QString &name, int adress)
{
    if(model->hasArincParametr(adress))
        model->getParametr(adress)->setName(name);
}

void ControllerArinc::setDimensionArincParametr(const QString &dim, int adress)
{
    if(model->hasArincParametr(adress))
        model->getParametr(adress)->setDimension(dim);
}

void ControllerArinc::setUnpackConst(double unpack, int adress)
{
    if(model->hasArincParametr(adress)){
        if(model->getParametr(adress)->Type()==Parametr::ARINC_DEC||
                model->getParametr(adress)->Type()==Parametr::ARINC_DEC_DISCR){
            ArincDecParametr *arincdec=dynamic_cast<ArincDecParametr*>(model->getParametr(adress));
            arincdec->setUnpackConst(unpack);
        }
    }
}

void ControllerArinc::setTypeParametr(Parametr::TypeParametr type, int adress)
{
    if(model->hasArincParametr(adress)){
        model->setTypeParametr(adress,type);
    }
}

void ControllerArinc::setStateContanier(StateContanier *cont, int adress)
{
    if(model->hasArincParametr(adress)){
        if(model->getParametr(adress)->Type()==Parametr::ARINC_DISCR){
            ArincDiscrParametr *arincdiscr=dynamic_cast<ArincDiscrParametr*>(model->getParametr(adress));
            arincdiscr->setStates(cont);
        }
    }
}

void ControllerArinc::clearArincParametrs()
{
    model->clearParametrs();
}

void ControllerArinc::buildGrafik(const QVector<TimeParametr> &p)
{
    cout<<"getLogsData!"<<endl;
    QVector<TimeParametr>::const_iterator iter;
    for(iter=p.begin();iter!=p.end();++iter)
        cout<<"time: "<<iter->time<<" value: 0x"<<hex<<iter->parametr<<endl<<dec;
}

void ControllerArinc::update()
{
    if(!model->isRunningArinc()){
        model->notifyObservers();
    }
}

void ControllerArinc::setRegisteredParametr(bool flag, int adress)
{
    model->getParametr(adress)->setRegistered(flag);
}

void ControllerArinc::buildDiscrsModel()
{
    foreach (int adress, discrs_models) {
        if(!form->containsDiscrModel(adress)){
            form->addDiscrTable(adress);
        }
    }
    if(discrs_models.empty())
        form->setVisibleDiscrTables(false);
    else
        form->setVisibleDiscrTables(true);
}



