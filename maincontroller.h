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
#include "device.h"
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
    QMap<int, ArincBoardInterface*> pciBoards;
    QMap<int, Device*> devices;
    FormConfParamsDevice *formConfDev;
    int countDevices;
    int countBoards;
    void connectActionsToSlots();
    int generateIndex();
signals:

public slots:
    void addDevice();
    void delDevice(int index);
    void confParamsDevice();
};

#endif // MAINCONTROLLER_H
