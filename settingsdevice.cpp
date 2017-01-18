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

SettingsArincDevice::SettingsArincDevice():SettingsDevice()
{

}

QList<ConfParametr *> *SettingsArincDevice::confParametrs()
{
    return &params;
}

void SettingsArincDevice::setConfParametrs(const QList<ConfParametr *> &p)
{
    params=p;
}

int SettingsArincDevice::getTimeStepToUpdateData() const
{
    return timeStepToUpdateData;
}

void SettingsArincDevice::setTimeStepToUpdateData(int value)
{
    timeStepToUpdateData = value;
}

int SettingsArincDevice::getTimeStepToWriteFile() const
{
    return timeStepToWriteFile;
}

void SettingsArincDevice::setTimeStepToWriteFile(int value)
{
    timeStepToWriteFile = value;
}

int SettingsArincDevice::getTimeStepToUpdateGraphs() const
{
    return timeStepToUpdateGraphs;
}

void SettingsArincDevice::setTimeStepToUpdateGraphs(int value)
{
    timeStepToUpdateGraphs = value;
}

