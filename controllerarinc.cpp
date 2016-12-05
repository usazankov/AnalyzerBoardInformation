#include "controllerarinc.h"

ControllerArinc::ControllerArinc(MainView *view, ArincModelInterface *model, int index)
{
    this->model=model;
    this->form=view->createMdiChild(this,model,index);
    this->index_contr=index;
}

ControllerArinc::~ControllerArinc()
{

}

void ControllerArinc::Start()
{
    model->startArinc();
}

void ControllerArinc::Stop()
{
    model->stopArinc();
    cout<<"Поток работает:"<<model->isRunningArinc()<<endl;

}

void ControllerArinc::addObserveredArincWord(int adress)
{
    model->addArincParametr(new ArincParametr(adress));
}

void ControllerArinc::addDiscrModel(int adress)
{
    form->addDiscrTable(adress);
}

void ControllerArinc::deleteDiscrModel(int adress)
{

}

void ControllerArinc::setTitleForm(const QString &name)
{
    form->setWindowTitle(name);
}

QString ControllerArinc::TitleForm() const
{
    return form->windowTitle();
}

int ControllerArinc::index()
{
    return index_contr;
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



