#include "arincdevice.h"

ArincDevice::ArincDevice(int index, ReadingBuffer<unsigned int *> *buf, MainView *view, QObject *obj):Device(index,obj)
{
    this->i=index;
    pciChannel=buf;
    this->view=view;
    Device::setName("Неизвестное устройство");
    form=view->createMdiChild(Device::name(),index);
    number_channel=buf->index();
    name_board=buf->name();
    reader=new ArincReader(pciChannel,this);
    form->setModel(reader);
    connect(form,SIGNAL(MdiFormDeleted(int)),view,SLOT(deleteMdiForm(int)));
    connect(form,SIGNAL(buildGrafik(int)),this,SLOT(buildGraf(int)));
    connect((dynamic_cast<ArincReader*>(reader)),SIGNAL(sendLogsData(QVector<TimeParametr>*)),this,SLOT(receiveData(QVector<TimeParametr>*)));
    connect(view,SIGNAL(MdiGrafCreated(int,int)),this,SLOT(mdiGrafCreated(int,int)));
    connect(view,SIGNAL(grafCreated(int,int,int)),this,SLOT(GrafCreated(int,int,int)));
    adressBuildGraf=0;
    indexBuildMdi=0;
    wasRun=0;
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
        //Применяем настройки региструремых параметров
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

        //Применяем параметры записи и отображения данных

        ArincReader::setTimeStepToUpdateData(s->getTimeStepToUpdateData());
        ArincReader::setTimeStepToWriteFile(s->getTimeStepToWriteFile());
        ArincReader::setLoadDataFromFile(s->getLoadDataFromFile());
        ModelTable::setTimeStepToUpdate(s->getTimeStepToUpdateTable());
        ModelDiscrTable::setTimeStepToUpdate(s->getTimeStepToUpdateTable());
        ArincGrafikPanel::setRestructData(s->getIsRestructData());
        ArincGrafikPanel::setTimeStepToUpdate(s->getTimeStepToUpdateData());
        ArincGrafikPanel::setRestructedStep(s->getReducedStep());
        ArincGrafikPanel::setStepToRestructData(static_cast<double>(s->getTimeStepToReduce()));
        MdiGrafForm::setDefaultTimeStepToUpdate(s->getTimeStepToUpdateGraphs());
        QList<int> l=grafmanager->indexsMdiForms(index());
        foreach (int i, l){
            MdiGrafForm* form=view->grafForm(i);
            form->setTimeStepToUpdate(s->getTimeStepToUpdateGraphs());
        }
        delete settings;
        if(!reader->isRunningArinc())
            reader->notifyObservers();
        cout<<"CONF APLYED!"<<endl;
    }
}

void ArincDevice::buildGraf(int adress)
{
    adressBuildGraf=adress;
    ArincParametr *p=reader->getParametr(adress);
    cout<<"buildGraf: "<<this->name().toStdString()<<endl;
    if(p!=Q_NULLPTR){
        int index=grafmanager->generateIndex();
        grafmanager->createGrafikMdiForm("График: "+p->Name()+" 0"+QString::number(p->Adress(),8), index, Device::index());
    }
}

void ArincDevice::receiveData(QVector<TimeParametr> *p)
{
    cout<<"adress=0"<<oct<<adressBuildGraf<<endl;
    cout<<this->name().toStdString()<<endl;
    grafmanager->setOldData(indexBuildMdi,adressBuildGraf,p,reader->getParametr(adressBuildGraf));

}

void ArincDevice::mdiGrafCreated(int indexOfMdi,int indexDevice)
{
    if(indexDevice==Device::index()){
        indexBuildMdi=indexOfMdi;
        view->grafForm(indexOfMdi)->setModel(reader);
        grafmanager->createGrafik(indexOfMdi, adressBuildGraf,indexDevice);
    }
}

void ArincDevice::GrafCreated(int adress, int indexOfMdi, int indexDevice)
{
    if(indexDevice==Device::index()){
        cout<<"Device in Thread:"<<this->thread()->objectName().toStdString()<<endl;
        //if(isRunningDev())//||(this->thread()->objectName()=="MainThread")
        reader->readValues(adress);
        view->activeMdiChild(view->currentActiveWindow());
        cout<<"GrafCreated: "<<name().toStdString()<<endl;
    }
}

void ArincDevice::start()
{
    reader->startArinc();
    grafmanager->addObserversMdiForm(index());
    ArincGrafikPanel::startTime=QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
    if(wasRun)
        grafmanager->clearData();
    wasRun=1;
    cout<<"start"<<endl;

}

void ArincDevice::stop()
{
    grafmanager->removeObserversMdiForm(index());
    reader->stopArinc();
    this->moveToThread(view->thread());
}

int ArincDevice::numberChannel()
{
    return number_channel;
}

QString ArincDevice::nameBoard()
{
    return name_board;
}

MdiForm *ArincDevice::MdiView() const
{
    return form;
}

bool ArincDevice::isRunningDev()
{
    return reader->isRunningArinc();
}

void ArincDevice::deleteAllObserveredGrafiks()
{
    grafmanager->removeObserversMdiForm(Device::index());
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

void ArincDevice::setName(const QString &name)
{
    Device::setName(name);
    form->setWindowTitle(Device::name());
}

void ArincDevice::setGrafikManager(GrafikManager *manager)
{
    grafmanager=manager;
    connect(this,SIGNAL(arincModelDeleted(int)),grafmanager,SLOT(modelIsDeleted(int)));
}


ArincDevice::~ArincDevice()
{
    emit arincModelDeleted(index());
    delete reader;
}

void ArincDevice::buildDiscrsModel()
{
    foreach (int adress, discrs_models){
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

