#include "maincontroller.h"

MainController::MainController(MainView *view, QObject *parent) : QObject(parent)
{
    this->view=view;
    countDevices=0;
    countBoards=0;
    formConfDev=Q_NULLPTR;
    connectActionsToSlots();
}

MainController::~MainController()
{
    foreach (ArincBoardInterface *board, pciBoards) {
        if (board!=0){
            delete board;
        }
        cout<<"deleted board"<<endl;
    }
    cout<<"cout dev="<<devices.count()<<endl;
    foreach (Device *dev, devices) {
        if (dev!=0)
            delete dev;
        cout<<"deleted dev"<<endl;
    }
    delete formConfDev;
}

void MainController::connectActionsToSlots()
{
    connect(view->action_add_device,SIGNAL(triggered()),this,SLOT(addDevice()));
    connect(view->action_confparams_device,SIGNAL(triggered()),this,SLOT(confParamsDevice()));

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

void MainController::addDevice()
{
    cout<<"Добавлено устройство"<<endl;
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
            cout<<"Created dev index="<<index<<endl;
            ++countDevices;
        }
    }
    delete form;

}

void MainController::delDevice(int index)
{
    delete devices[index];
    devices.remove(index);
    std::cout<<"Deleted index="<<index<<std::endl;
    if(formConfDev!=Q_NULLPTR)
        formConfDev->deleteChannel(index);
    --countDevices;
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
    }
    if(formConfDev->exec()==FormConfParamsDevice::Accepted){

    }

}
