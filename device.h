#ifndef DEVICE_H
#define DEVICE_H

#include <readingbuffer.h>
#include "arincreader.h"
#include "controllerarinc.h"
#include "modelconfparams.h"
#include <QObject>
class Device:public QObject
{
    Q_OBJECT
public:
    explicit Device(int index, ReadingBuffer<unsigned int*> *buf, MdiForm *form);
    int index()const;
    QString title()const;
    void applyConf(const QList<ConfParametr*> &list);
    int numberChannel();
    QString nameBoard();
    bool isRunningDev();

    virtual ~Device();
private:
    int i;//Индекс Device
    int number_channel;
    QString name_board;
    ArincModelInterface *reader;
    ReadingBuffer<unsigned int*>* pciChannel;
    ControllerInterface* controller;
    MdiForm *form;
    bool wasRun;
public slots:
    void startDev();
    void stopDev();

};

#endif // DEVICE_H
