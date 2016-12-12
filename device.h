#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>
#include <readingbuffer.h>
#include "arincreader.h"
#include "controllerarinc.h"
#include "modelconfparams.h"
class Device
{
public:
    explicit Device(int index, ReadingBuffer<unsigned int*> *buf, MdiForm *form);
    int index()const;
    QString title()const;
    void applyConf(const QList<ConfParametr*> &list);
    virtual ~Device();
private:
    int i;//Индекс Device
    ArincReader *reader;
    ReadingBuffer<unsigned int*>* pciChannel;
    ControllerArinc* controller;
};

#endif // DEVICE_H
