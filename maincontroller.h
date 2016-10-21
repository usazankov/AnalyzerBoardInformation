#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include "mainview.h"
#include "controllerarinc.h"
#include "arincmodelinterface.h"
#include "arincreader.h"
#include "arincboardpci429linux.h"
#include <iostream>

using namespace std;
class MainController : public QObject
{
    Q_OBJECT
public:
    explicit MainController(QObject *parent);
    explicit MainController(MainView *view, QObject *parent = 0);
    ~MainController();
private:
    QVector<ArincBoardlPCI429*> pciBoards;
    QVector<ArincChannelPCI429*> pciChannels;
    QVector<ArincReader*> readers;
    QVector<ControllerArinc*> controllers;
    MainView *view;
signals:

public slots:
};

#endif // MAINCONTROLLER_H
