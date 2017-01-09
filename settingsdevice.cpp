#include "settingsdevice.h"

SettingsDevice::SettingsDevice()
{

}

dev::TypeDevice SettingsDevice::typeSettings() const
{
    if (typeid(*this)==typeid(SettingsArincDevice))
        return dev::ArincDevice;
    else return dev::ArincDevice;
}

SettingsDevice::~SettingsDevice()
{

}

SettingsArincDevice::SettingsArincDevice(const QList<ConfParametr *> &list):SettingsDevice()
{
    params=list;
}

QList<ConfParametr *> *SettingsArincDevice::confParametrs()
{
    return &params;
}
