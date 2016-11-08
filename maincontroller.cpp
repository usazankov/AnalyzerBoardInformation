#include "maincontroller.h"

MainController::MainController(MainView *view, QObject *parent) : QObject(parent)
{
    this->view=view;
    coutMVC=0;
    coutBoards=0;
    connectActionsToSlots();
}


MainController::~MainController()
{
    foreach (ArincBoardlPCI429 *board, pciBoards) {
        if (board!=0){
            delete board;

        }
        cout<<"deleted board"<<endl;
    }

    foreach (ArincChannelPCI429 *channel, pciChannels) {
        if(channel!=0)
         delete channel;
        cout<<"deleted channel"<<endl;
    }
    foreach (ArincReader *reader, readers) {
        if(reader!=0){
            reader->quit();
            reader->wait();
            delete reader;
        }
        cout<<"deleted reader"<<endl;
    }
    foreach (ControllerArinc *contr, controllers) {
        if (contr!=0)
            delete contr;
        cout<<"deleted contr"<<endl;
    }
}

void MainController::connectActionsToSlots()
{
    connect(view->action_add_device,SIGNAL(triggered()),this,SLOT(addDevice()));
    connect(view->action_confparams_device,SIGNAL(triggered()),this,SLOT(confParamsDevice()));

}

void MainController::addDevice()
{
    cout<<"Добавлено устройство"<<endl;
    FormAddDevice *form = new FormAddDevice(view);

    if(form->exec()==FormAddDevice::Accepted){
        ArincChannelPCI429 *channel;
        if(!pciBoards.empty()){
            bool flagToNotHasBoard=1;
            foreach (ArincBoardlPCI429 *board, pciBoards){
                cout<<"boardName="<<board->boardName().toStdString()<<endl;
                cout<<"nameDevice="<<form->nameDevice().toStdString().c_str()<<endl;
                if(board->boardName()==form->nameDevice()){

                    channel=new ArincChannelPCI429(board,form->numberChannel(),1, coutMVC);
                    pciChannels[coutMVC]=channel;
                    flagToNotHasBoard=0;
                }
            }
            if(flagToNotHasBoard){
                ArincBoardlPCI429 *board=new ArincBoardlPCI429(form->nameDevice().toStdString().c_str(),coutBoards);
                pciBoards[coutBoards]=board;
                ++coutBoards;
                channel=new ArincChannelPCI429(board,form->numberChannel(),1, coutMVC);
                pciChannels[coutMVC]=channel;
            }
        }else{
            ArincBoardlPCI429 *board=new ArincBoardlPCI429(form->nameDevice().toStdString().c_str(),coutBoards);
            pciBoards[coutBoards]=board;
            ++coutBoards;
            channel=new ArincChannelPCI429(board,form->numberChannel(),1, coutMVC);
            pciChannels[coutMVC]=channel;
        }

        ArincReader *reader=new ArincReader(channel,coutMVC);
        readers[coutMVC]=reader;
        ControllerArinc *controller=new ControllerArinc(view,reader,coutMVC);
        controller->setTitleForm(form->nameChannel());
        controllers[coutMVC]=controller;
        connect(controller->getMdiForm(), SIGNAL(MdiFormDeleted(int)), this, SLOT(delDevice(int)));
        controller->Start();
        ++coutMVC;
    }
    delete form;
}

void MainController::delDevice(int index)
{

    foreach (ControllerArinc *cont, controllers) {
        if(cont->index()==index){
            delete cont;
            controllers.remove(index);
        }
    }
    foreach (ArincReader *reader, readers) {
        if(reader->indexM()==index){
            reader->quit();
            reader->wait();
            delete reader;
            readers.remove(index);
        }
    }
    foreach (ArincChannelPCI429 *channel, pciChannels) {
        if(channel->indexChannel()==index){
            delete channel;
            pciChannels.remove(index);
        }
    }

    --coutMVC;
}

void MainController::confParamsDevice()
{
    FormConfParamsDevice *form = new FormConfParamsDevice(view);
    if(form->exec()==FormConfParamsDevice::Accepted){

    }
    delete form;
}
