#include "device.h"

Device::Device(int index, ReadingBuffer<unsigned int *> *buf, MdiForm *form)
{
    this->i=index;
    reader=new ArincReader(buf);
    form->setModel(reader);
    controller=new ControllerArinc(form,reader);
    controller->addObserveredArincWord(0307);
    controller->setNameArincParametr("Параметр1",0307);
    controller->addObserveredArincWord(0300);
    controller->addObserveredArincWord(0311);
    controller->setNameArincParametr("Параметр2",0300);
    controller->setDimensionArincParametr("Км.ч",0300);
    controller->addObserveredArincWord(0310);
    StateContanier *states=new StateContanier();
    states->insertState(new State(5,"5-Состояние:","0 - Нет","1 - Да"));
    states->insertState(new State(6,"6-Состояние:","0 - Нет","1 - Да"));
    states->insertState(new State(7,"7-Состояние:","0 - Нет","1 - Да"));
    states->insertState(new State(8,"8-Состояние:","0 - Нет","1 - Да"));
    states->insertState(new State(9,"9-Состояние:","0 - Нет","1 - Да"));
    controller->setTypeParametr(Parametr::ARINC_DISCR,0300);
    controller->setStateContanier(states,0300);
    controller->setTypeParametr(Parametr::ARINC_DISCR,0307);
    controller->setStateContanier(states,0307);
    controller->setTypeParametr(Parametr::ARINC_DISCR,0310);
    controller->setStateContanier(states,0310);
    controller->setTypeParametr(Parametr::ARINC_DEC,0311);
    controller->setUnpackConst(90,0311);
    controller->setDimensionArincParametr("км.ч",0311);
    controller->Start();
}

int Device::index() const
{
    return i;
}

QString Device::title() const
{
    return controller->TitleForm();
}

Device::~Device()
{
    reader->quit();
    reader->wait();
    delete reader;
    delete controller;
}
