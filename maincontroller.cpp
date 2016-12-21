#include "maincontroller.h"

MainController::MainController(MainView *view, QObject *parent) : QObject(parent)
{
    this->view=view;
    countDevices=0;
    countBoards=0;
    formConfDev=Q_NULLPTR;
    connectActionsToSlots();
    checkActions();
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
        view->action_del_device->setEnabled(false);
        view->action_start->setEnabled(false);
        view->action_stop->setEnabled(false);
        view->action_save_file->setEnabled(false);
    }else{
        if(!ThreadsisRunning())
            view->action_start->setEnabled(true);
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
            MdiForm *mdi=view->createMdiChild(form->nameChannel(),index);
            connect(mdi, SIGNAL(MdiFormDeleted(int)), this, SLOT(delDevice(int)));
            Device* dev = new Device(index,channel,mdi);
            devices[index]=dev; 
            QThread *thread = new QThread;
            dev->moveToThread(thread);
            if(ThreadsisRunning())
                thread->start();
            threads[index]=thread;
            connect(thread,SIGNAL(started()),dev,SLOT(startDev()));
            connect(thread,SIGNAL(finished()),dev,SLOT(stopDev()));
            cout<<"Created dev index="<<index<<endl;
            ++countDevices;
        }
    }
    delete form;
    checkActions();
}

void MainController::delDevice(int index)
{
    int channel=devices[index]->numberChannel();
    QString nameBoard=devices[index]->nameBoard();
    int indexBoard;
    threads[index]->quit();
    threads[index]->wait();
    delete devices[index];
    devices.remove(index);
    delete threads[index];
    threads.remove(index);
    foreach (ArincBoardInterface *item, pciBoards){
        if(item->boardName()==nameBoard){
            indexBoard=pciBoards.key(item);
        }
    }
    pciBoards[indexBoard]->deleteChannel(channel);
    std::cout<<"Deleted index="<<index<<std::endl;
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
            formConfDev->insertChannel(dev->title(), dev->index());
        else if(formConfDev->ContainsChannel(Ui::EMPTY_CHANNEL)){
            formConfDev->renameChannel(dev->title(),dev->index());
        }
    }
    if(formConfDev->ChannelsIsEmpty()){
        formConfDev->insertChannel(Ui::EMPTY_CHANNEL, 0);
    }
    if(formConfDev->exec()==FormConfParamsDevice::Accepted){
        foreach (Device *dev, devices) {
            dev->applyConf(formConfDev->conf(dev->index()));
            cout<<"APPLYED! index="<<dev->index()<<endl;
        }
    }
}

void MainController::startDevice()
{
    foreach (QThread *t, threads)
        if(!t->isRunning())
            t->start();
    view->action_stop->setEnabled(true);
    view->action_start->setEnabled(false);
}

void MainController::stopDevice()
{
    foreach (QThread *t, threads) {
        if(!t->isFinished())
            t->quit();
    }
    view->action_start->setEnabled(true);
    view->action_stop->setEnabled(false);
}
