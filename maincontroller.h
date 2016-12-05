#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include "controllerarinc.h"
#include "arincmodelinterface.h"
#include "arincreader.h"
#include "arincboardpci429linux.h"
#include "formadddevice.h"
#include "formconfparamsdevice.h"
#include <iostream>

namespace Ui {
class MainController;
}
using namespace std;
class MainController : public QObject
{
    Q_OBJECT
public:
    explicit MainController(MainView *view, QObject *parent = 0);

    ~MainController();
private:
    MainView *view;
    QMap<int, ArincBoardlPCI429*> pciBoards;
    QMap<int, ArincChannelPCI429*> pciChannels;
    QMap<int, ArincReader*> readers;
    QMap<int, ControllerArinc*> controllers;

    FormConfParamsDevice *formConfDev;
    int coutMVC;
    int coutBoards;
    void connectActionsToSlots();
    int generateIndex();
signals:

public slots:
    void addDevice();
    void delDevice(int index);
    void confParamsDevice();
};

#endif // MAINCONTROLLER_H
