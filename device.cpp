#include "device.h"

Device::Device(int index, ReadingBuffer<unsigned int *> *buf, MdiForm *form)
{
    this->i=index;
    reader=new ArincReader(buf);
    form->setModel(reader);
    controller=new ControllerArinc(form,reader);
    number_channel=buf->numberChannel();
    name_board=buf->nameBoard();
    /*controller->addObserveredArincWord(0307);
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
    controller->setDimensionArincParametr("км.ч",0311);*/
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

void Device::applyConf(const QList<ConfParametr *> &list)
{
    controller->clearArincParametrs();
    controller->deleteAllDiscrModel();
    foreach (ConfParametr* item, list){
        controller->addObserveredArincWord(item->adress);
        controller->setNameArincParametr(item->name,item->adress);
        controller->setDimensionArincParametr(item->dimension,item->adress);
        switch(item->type){
        case DEC:{
            ConfDecParametr *p=dynamic_cast<ConfDecParametr*>(item);
            controller->setTypeParametr(Parametr::ARINC_DEC,p->adress);
            controller->setUnpackConst(p->unpack,p->adress);
            break;
        }
        case DISCR:{
            ConfDiscrParametr *p=dynamic_cast<ConfDiscrParametr*>(item);
            controller->setTypeParametr(Parametr::ARINC_DISCR,p->adress);
            controller->setStateContanier(p->model.getStates(),p->adress);
            controller->addDiscrModel(p->adress);
            break;
        }
        case DISCR_DEC:{

            break;
        }
        case DD:{

            break;
        }
        default:
            break;
        }
    }
}

int Device::numberChannel()
{
    return number_channel;
}

QString Device::nameBoard()
{
    return name_board;
}

Device::~Device()
{
    controller->Stop();
    delete reader;
    delete controller;
}
