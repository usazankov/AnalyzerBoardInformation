#include "maincontroller.h"

MainController::MainController(MainView *view, QObject *parent) : QObject(parent)
{
    this->view=view;

    connectActionsToSlots();
}

QVector<ArincBoardlPCI429 *> MainController::PCIBoards()
{
    return pciBoards;
}

QVector<ArincChannelPCI429 *> MainController::PCIChannels()
{
    return pciChannels;
}

QVector<ArincReader *> MainController::Readers()
{
    return readers;
}

QVector<ControllerArinc *> MainController::Controllers()
{
    return controllers;
}

MainController::~MainController()
{
    foreach (ArincBoardlPCI429 *board, pciBoards) {
        delete board;
        cout<<"deleted board"<<endl;
    }

    foreach (ArincChannelPCI429 *channel, pciChannels) {
        delete channel;
        cout<<"deleted channel"<<endl;
    }
    foreach (ArincReader *reader, readers) {
        delete reader;
        cout<<"deleted reader"<<endl;
    }
    foreach (ControllerArinc *contr, controllers) {
        delete contr;
        cout<<"deleted contr"<<endl;
    }
}

void MainController::connectActionsToSlots()
{
    connect(view->action_add_device,SIGNAL(triggered()),this,SLOT(addDevice()));
}

void MainController::addDevice()
{
    cout<<"Добавлено устройство"<<endl;
    FormAddDevice *form = new FormAddDevice(view);

    if(form->exec()==FormAddDevice::Accepted){
        ArincBoardlPCI429 *board=new ArincBoardlPCI429(form->nameDevice().toStdString().c_str(),8);
        pciBoards.push_back(board);
        ArincChannelPCI429 *channel=new ArincChannelPCI429(board,form->numberChannel(),1);
        pciChannels.push_back(channel);
        ArincReader *reader=new ArincReader(channel);
        readers.push_back(reader);
        ControllerArinc *controller=new ControllerArinc(view,reader);
        controllers.push_back(controller);
        controller->Start();
    }
    delete form;
}
