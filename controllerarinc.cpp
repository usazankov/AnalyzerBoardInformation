#include "controllerarinc.h"

ControllerArinc::ControllerArinc(ArincModelInterface *model, MainView *view)
{
    this->model=model;
    this->view=view;
    this->form=view->createMdiChild(this,model);
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

