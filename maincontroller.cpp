#include "maincontroller.h"

MainController::MainController(MainView *view, QObject *parent) : QObject(parent)
{
    this->view=view;
    countDevices=0;
    countBoards=0;
    formConfDev=Q_NULLPTR;
    connectActionsToSlots();
    checkActions();
    this->thread()->setObjectName("MainThread");
    grafManager=new GrafikManager(view,this);
}

MainController::~MainController()
{
    cout<<"cout dev="<<devices.count()<<endl;
    foreach (Device *dev, devices) {
        if (dev!=Q_NULLPTR){
            delDevice(dev->index());
        }
        cout<<"deleted dev"<<endl;
    }
    foreach (ArincBoardInterface *board, pciBoards) {
        if (board!=Q_NULLPTR){
            delete board;
        }
        cout<<"deleted board"<<endl;
    }
    delete formConfDev;
}

void MainController::connectActionsToSlots()
{
    connect(view->action_add_device,SIGNAL(triggered()),this,SLOT(addDevice()));
    connect(view->action_del_device,SIGNAL(triggered()),this,SLOT(delDevice()));
    connect(view->action_confparams_device,SIGNAL(triggered()),this,SLOT(confParamsDevice()));
    connect(view->action_start,SIGNAL(triggered()),this,SLOT(startDevice()));
    connect(view->action_stop,SIGNAL(triggered()),this,SLOT(stopDevice()));
}

int MainController::generateIndex()
{
    int i=0;
    while(true){
        if(!devices.contains(i)){
            return i;
        }
        ++i;
    }
}

bool MainController::ThreadsisRunning()
{
    bool threadIsRunning=0;
    foreach (QThread *t, threads) {
        if(t->isRunning())
            threadIsRunning=1;
    }
    return threadIsRunning;
}

void MainController::checkActions()
{
    if(devices.isEmpty()){
        view->action_add_device->setEnabled(true);
        view->action_del_device->setEnabled(false);
        view->action_start->setEnabled(false);
        view->action_stop->setEnabled(false);
        view->action_save_file->setEnabled(false);
        view->action_start->setChecked(false);
    }else{
        if(!ThreadsisRunning()){
            view->action_start->setEnabled(true);

        }
        view->action_save_file->setEnabled(true);
        view->action_del_device->setEnabled(true);

    }
}

void MainController::addDevice()
{
    int index=generateIndex();
    FormAddDevice *form = new FormAddDevice(view);
    if(form->exec()==FormAddDevice::Accepted){
        QString nameDev=form->nameDevice();
        int indexDev;
        bool hasDev=false;
        ArincBoardInterface *arincBoard;
        ReadingBuffer<unsigned int*> *channel=Q_NULLPTR;
        //Создаем Arinc-плату
        foreach (ArincBoardInterface *item, pciBoards){
            if(item->boardName()==nameDev){
                hasDev=true;
                indexDev=pciBoards.key(item);
            }
        }
        if(hasDev){
            arincBoard=pciBoards[indexDev];
            if(!arincBoard->containsChannel(form->numberChannel()))
                channel=arincBoard->createChannel(form->numberChannel(),1);
        }else{
            switch (form->typeDev()){
            case dev::ArincPCI429:
                    arincBoard=new ArincBoardlPCI429(nameDev, countBoards);
                break;
            case dev::ArincMPC429:
                    arincBoard=new ArincBoardMPC429(nameDev, countBoards);
                break;
            default:
                break;
            }
            pciBoards[countBoards]=arincBoard;
            channel=arincBoard->createChannel(form->numberChannel(),1);
            ++countBoards;
        }
        if(channel!=Q_NULLPTR){            
            Device* dev = new ArincDevice(index,channel,view);
            connect((dynamic_cast<ArincDevice*>(dev))->MdiView(), SIGNAL(MdiFormDeleted(int)), this, SLOT(delDevice(int)));
            devices[index]=dev; 
            dev->setName(form->nameChannel());
            dynamic_cast<ArincDevice*>(dev)->setGrafikManager(grafManager);
            QThread *thread = new QThread;
            thread->setObjectName(form->nameChannel());
            threads[index]=thread;
            connect(thread,SIGNAL(started()),dev,SLOT(start()));
            connect(thread,SIGNAL(finished()),dev,SLOT(stop()));
            cout<<"Created dev index="<<index<<endl;
            ++countDevices;
        }
    }
    delete form;
    checkActions();
}

void MainController::delDevice(int index)
{
    if(devices[index]->typeDevice()==dev::ArincDevice){
        ArincDevice *dev=dynamic_cast<ArincDevice*>(devices[index]);
        int channel=dev->numberChannel();
        QString nameBoard=dev->nameBoard();
        int indexBoard;
        threads[index]->quit();
        threads[index]->wait();
        delete threads[index];
        threads.remove(index);
        delete devices[index];
        devices.remove(index);
        foreach (ArincBoardInterface *item, pciBoards){
            if(item->boardName()==nameBoard){
                indexBoard=pciBoards.key(item);
            }
        }
        pciBoards[indexBoard]->deleteChannel(channel);
        std::cout<<"Deleted index="<<index<<std::endl;
    }

    if(formConfDev!=Q_NULLPTR)
        formConfDev->deleteChannel(index);
    --countDevices;
    checkActions();
}

void MainController::delDevice()
{
    view->closeActiveMdiForm();
}

void MainController::confParamsDevice()
{
    if(formConfDev==Q_NULLPTR){
        formConfDev = new FormConfParamsDevice(view);
    }else
        formConfDev->show();
    foreach (Device *dev, devices) {
        if(!formConfDev->ContainsChannel(dev->index()))
            formConfDev->insertChannel(dev->name(), dev->index());
        else if(formConfDev->ContainsChannel(Ui::EMPTY_CHANNEL)){
            formConfDev->renameChannel(dev->name(),dev->index());
        }
    }
    if(formConfDev->ChannelsIsEmpty()){
        formConfDev->insertChannel(Ui::EMPTY_CHANNEL, 0);
    }
    if(formConfDev->exec()==FormConfParamsDevice::Accepted){
        foreach (Device *dev, devices) {
            dev->setSettingsDevice(formConfDev->conf(dev->index()));
            cout<<"APPLYED! index="<<dev->index()<<endl;
        }
    }
}

void MainController::startDevice()
{
    QMap<int,QThread*>::iterator iter;
    for(iter=threads.begin();iter!=threads.end();++iter){
        devices[iter.key()]->moveToThread(iter.value());
        if(!iter.value()->isRunning())
            iter.value()->start();
    }
    /*foreach (QThread *t, threads)
        if(!t->isRunning()){
            t->start();
        }*/
    view->action_stop->setEnabled(true);
    view->action_start->setEnabled(false);
    view->action_start->setChecked(true);
    view->action_add_device->setEnabled(false);
    view->action_del_device->setEnabled(false);

    view->activeMdiChild(view->currentActiveWindow());
}

void MainController::stopDevice()
{
    foreach (QThread *t, threads) {
        if(!t->isFinished())
            t->quit();
    }
//    foreach (Device *dev, devices)
//        dev->moveToThread(this->thread());
    view->action_start->setEnabled(true);
    view->action_stop->setEnabled(false);
    view->action_start->setChecked(false);
    view->action_add_device->setEnabled(true);
    view->action_del_device->setEnabled(true);
}
