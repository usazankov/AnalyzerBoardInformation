#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include "controllerarinc.h"
#include "arincmodelinterface.h"
#include "arincreader.h"
#include "arincboardpci429linux.h"
#include "formadddevice.h"
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
    QVector<ArincBoardlPCI429*> PCIBoards();
    QVector<ArincChannelPCI429*> PCIChannels();
    QVector<ArincReader*> Readers();
    QVector<ControllerArinc*> Controllers();
    ~MainController();
private:
    MainView *view;
    QVector<ArincBoardlPCI429*> pciBoards;
    QVector<ArincChannelPCI429*> pciChannels;
    QVector<ArincReader*> readers;
    QVector<ControllerArinc*> controllers;
    void connectActionsToSlots();
signals:

public slots:
    void addDevice();
};

#endif // MAINCONTROLLER_H
