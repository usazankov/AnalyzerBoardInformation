#ifndef DEVICE_H
#define DEVICE_H

#include <ArincBoards/arincintefaces.h>
#include "arincreader.h"
#include "FormsModels/modelconfparams.h"
#include "FormsModels/mdiform.h"
#include "device.h"
#include <QObject>
class ArincDevice: public Device
{
    Q_OBJECT
public:
    explicit ArincDevice(int index, ReadingBuffer<unsigned int*> *buf, MdiForm *form, QObject *obj=0);
    QString title()const;
    int numberChannel();
    QString nameBoard();
    bool isRunningDev();
    virtual ~ArincDevice();
private:
    int i;//Индекс Device
    QList<int> discrs_models;
    int number_channel;
    QString name_board;
    ArincModelInterface *reader;
    ReadingBuffer<unsigned int*>* pciChannel;
    MdiForm *form;
    bool wasRun;
    void buildDiscrsModel();
    void deleteDiscrTable(int adress);
    void deleteAllDiscrTable();
    void applyConf();
    // Device interface
public:
    void start();
    void stop();

    // Device interface
public:
    void setSettingsDevice(SettingsDevice *settings);

    // Device interface
public:
    dev::TypeDevice typeDevice() const;
};

#endif // DEVICE_H
