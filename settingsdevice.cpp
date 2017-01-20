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

bool SettingsArincDevice::getIsRestructData() const
{
    return restructData;
}

void SettingsArincDevice::setIsRestructData(bool value)
{
    restructData = value;
}

int SettingsArincDevice::getTimeStepToUpdateTable() const
{
    return timeStepToUpdateTable;
}

void SettingsArincDevice::setTimeStepToUpdateTable(int value)
{
    timeStepToUpdateTable = value;
}

bool SettingsArincDevice::getLoadDataFromFile() const
{
    return loadDataFromFile;
}

void SettingsArincDevice::setLoadDataFromFile(bool value)
{
    loadDataFromFile = value;
}

double SettingsArincDevice::getReducedStep() const
{
    return reducedStep;
}

void SettingsArincDevice::setReducedStep(double value)
{
    reducedStep = value;
}

int SettingsArincDevice::getTimeStepToReduce() const
{
    return timeStepToReduce;
}

void SettingsArincDevice::setTimeStepToReduce(int value)
{
    timeStepToReduce = value;
}

