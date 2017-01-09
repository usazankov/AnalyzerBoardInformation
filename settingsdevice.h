#ifndef SETTINGSDEVICE_H
#define SETTINGSDEVICE_H
#include <QList>
#include <typeinfo>
namespace dev {
    enum TypeDevice{NullDevice,ArincDevice};
}
struct ConfParametr;
class SettingsDevice{
public:
    explicit SettingsDevice();
    QString name;
    virtual dev::TypeDevice typeSettings()const;
    virtual ~SettingsDevice();
};

class SettingsArincDevice:public SettingsDevice
{
public:
    explicit SettingsArincDevice(const QList<ConfParametr*> &list);
    QList<ConfParametr*>* confParametrs();
private:
    QList<ConfParametr*> params;
};
#endif // SETTINGSDEVICE_H
