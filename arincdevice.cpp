#include "arincdevice.h"

ArincDevice::ArincDevice(int index, ReadingBuffer<unsigned int *> *buf, MdiForm *form, QObject *obj):Device(index,obj)
{
    this->i=index;
    pciChannel=buf;
    this->form=form;
    number_channel=buf->index();
    name_board=buf->name();
    reader=new ArincReader(pciChannel,this);
    form->setModel(reader);
}

QString ArincDevice::title() const
{
    return form->windowTitle();
}

void ArincDevice::applyConf()
{
    SettingsArincDevice *s=Q_NULLPTR;
    if(this->settings->typeSettings()==dev::ArincDevice)
        s=dynamic_cast<SettingsArincDevice*>(this->settings);
    if(s!=Q_NULLPTR){
        QList<ConfParametr*> list=*(s->confParametrs());
        cout<<"CONF BEGIN!"<<endl;
        reader->clearParametrs();
        deleteAllDiscrTable();
        foreach (ConfParametr* item, list){
            int adress=item->adress;
            reader->addArincParametr(adress);
            if(reader->hasArincParametr(adress)){
                reader->getParametr(adress)->setName(item->name);
                reader->getParametr(adress)->setDimension(item->dimension);
                reader->getParametr(adress)->setRegistered(true);
                switch(item->type){
                case params::DEC:{
                    ConfDecParametr *p=dynamic_cast<ConfDecParametr*>(item);
                    reader->setTypeParametr(p->adress,Parametr::ARINC_DEC);
                    ArincDecParametr *arincdec=dynamic_cast<ArincDecParametr*>(reader->getParametr(adress));
                    arincdec->setUnpackConst(p->unpack);
                    break;
                }
                case params::DISCR:{
                    ConfDiscrParametr *p=dynamic_cast<ConfDiscrParametr*>(item);
                    reader->setTypeParametr(p->adress,Parametr::ARINC_DISCR);
                    if(reader->getParametr(adress)->Type()==Parametr::ARINC_DISCR){
                        ArincDiscrParametr *arincdiscr=dynamic_cast<ArincDiscrParametr*>(reader->getParametr(adress));
                        arincdiscr->setStates(p->model.getStates());
                    }
                    if(!discrs_models.contains(adress)){
                        discrs_models.push_back(adress);
                    }
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
        }
        delete settings;
        cout<<"CONF APLYED!"<<endl;
    }
}

void ArincDevice::start()
{
    reader->startArinc(1);
}

void ArincDevice::stop()
{
    reader->stopArinc();
}

int ArincDevice::numberChannel()
{
    return number_channel;
}

QString ArincDevice::nameBoard()
{
    return name_board;
}

bool ArincDevice::isRunningDev()
{
    return reader->isRunningArinc();
}

void ArincDevice::setSettingsDevice(SettingsDevice *settings)
{
    this->settings=settings;
    applyConf();
    buildDiscrsModel();
    if(!reader->isRunningArinc()){
        reader->notifyObservers();
    }
}

dev::TypeDevice ArincDevice::typeDevice() const
{
    return dev::ArincDevice;
}


ArincDevice::~ArincDevice()
{
    delete reader;
}

void ArincDevice::buildDiscrsModel()
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

void ArincDevice::deleteDiscrTable(int adress)
{
    discrs_models.removeOne(adress);
    form->deleteDiscrTable(adress);
}

void ArincDevice::deleteAllDiscrTable()
{
    while(!discrs_models.empty()){
        deleteDiscrTable(discrs_models.back());
    }
}

