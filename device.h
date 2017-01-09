#ifndef DEVICEINTERFACE_H
#define DEVICEINTERFACE_H
#include "settingsdevice.h"
#include <QObject>
class Device:public QObject{
    Q_OBJECT
public:
    explicit Device(int index, QObject* parent=Q_NULLPTR);
    virtual ~Device();
    int index()const;
    QString name()const;
    void setName(const QString &name);
    dev::TypeDevice virtual typeDevice()const=0;
    virtual void setSettingsDevice(SettingsDevice* settings);
public slots:
    virtual void start()=0;
    virtual void stop()=0;
private:
    int i;//Индекс
    QString n;//Имя
protected:
    SettingsDevice* settings;
};
#endif // DEVICEINTERFACE_H
