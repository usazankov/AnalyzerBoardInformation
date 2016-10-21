#include "maincontroller.h"

MainController::MainController(QObject *parent) : QObject(parent)
{

}

MainController::MainController(MainView *view, QObject *parent) : QObject(parent)
{
    this->view=view;
    ArincBoardlPCI429 *board=new ArincBoardlPCI429("dev/pci429_0",8);
    pciBoards.push_back(board);
    ArincChannelPCI429 *channel=new ArincChannelPCI429(board,1,1);
    pciChannels.push_back(channel);
    ArincReader *reader=new ArincReader(channel);
    readers.push_back(reader);
    reader->start();
    ControllerArinc *controller=new ControllerArinc(reader,view);
    controllers.push_back(controller);

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
