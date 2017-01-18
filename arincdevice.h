#ifndef DEVICE_H
#define DEVICE_H

#include <ArincBoards/arincintefaces.h>
#include "arincreader.h"
#include "UnpackingArinc/parametr_impl.h"
#include "FormsModels/modelconfparams.h"
#include "FormsModels/mainview.h"
#include "grafikmanager.h"
#include "device.h"
#include <QObject>
class ArincDevice: public Device
{
    Q_OBJECT
public:
    explicit ArincDevice(int index, ReadingBuffer<unsigned int*> *buf, MainView *view, QObject *obj=0);
    QString title()const;
    int numberChannel();
    QString nameBoard();
    MdiForm* MdiView()const;
    bool isRunningDev();
    void deleteAllObserveredGrafiks();
    virtual ~ArincDevice();
    // Device interface
    void start();
    void stop();
    void setSettingsDevice(SettingsDevice *settings);
    dev::TypeDevice typeDevice() const;
    void setName(const QString &name);
    void setGrafikManager(GrafikManager* manager);
private:
    QList<int> discrs_models;
    int number_channel;
    QString name_board;
    ArincModelInterface *reader;
    ReadingBuffer<unsigned int*>* pciChannel;
    MdiForm *form;
    MainView *view;
    GrafikManager *grafmanager;
    int adressBuildGraf;
    int indexBuildMdi;
    bool wasRun;
    void setTimeStepToUpdateGraphiks(int timeStep);
    void buildDiscrsModel();
    void deleteDiscrTable(int adress);
    void deleteAllDiscrTable();
    void applyConf();
signals:
    void arincModelDeleted(int indexDevice);
public slots:
    void receiveData(QVector<TimeParametr> *p);
    void mdiGrafCreated(int indexOfMdi, int indexDevice);
    void GrafCreated(int adress,int indexOfMdi,int indexDevice);
    void buildGraf(int adress);
};

#endif // DEVICE_H
