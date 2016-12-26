#include "device.h"

Device::Device(int index, ReadingBuffer<unsigned int *> *buf, MdiForm *form)
{
    this->i=index;
    pciChannel=buf;
    this->form=form;
    number_channel=buf->index();
    name_board=buf->name();
    reader=new ArincReader(pciChannel,this);
    form->setModel(reader);
    controller=new ControllerArinc(form,reader);
}

int Device::index() const
{
    return i;
}

QString Device::title() const
{
    return form->windowTitle();
}

void Device::applyConf(const QList<ConfParametr *> &list)
{
    cout<<"CONF BEGIN!"<<endl;
    controller->clearArincParametrs();
    controller->deleteAllDiscrModel();
    foreach (ConfParametr* item, list){
        controller->addObserveredArincWord(item->adress);
        controller->setNameArincParametr(item->name,item->adress);
        controller->setDimensionArincParametr(item->dimension,item->adress);
        controller->setRegisteredParametr(true,item->adress);
        switch(item->type){
        case params::DEC:{
            ConfDecParametr *p=dynamic_cast<ConfDecParametr*>(item);
            controller->setTypeParametr(Parametr::ARINC_DEC,p->adress);
            controller->setUnpackConst(p->unpack,p->adress);
            break;
        }
        case params::DISCR:{
            ConfDiscrParametr *p=dynamic_cast<ConfDiscrParametr*>(item);
            controller->setTypeParametr(Parametr::ARINC_DISCR,p->adress);
            controller->setStateContanier(p->model.getStates(),p->adress);
            controller->addDiscrModel(p->adress);
            break;
        }
        case params::DISCR_DEC:{

            break;
        }
        case params::DD:{

            break;
        }
        default:
            break;
        }
    }
    controller->buildDiscrsModel();
    controller->update();
    cout<<"CONF APLYED!"<<endl;
}

int Device::numberChannel()
{
    return number_channel;
}

QString Device::nameBoard()
{
    return name_board;
}

bool Device::isRunningDev()
{
    return reader->isRunningArinc();
}

void Device::stopDev()
{
    controller->Stop();
}

void Device::startDev()
{
    controller->Start(1);
}

Device::~Device()
{
    delete reader;
    delete controller;
}

