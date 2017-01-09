#include "device.h"

Device::Device(int index, QObject *parent):QObject(parent)
{
    i=index;
}

Device::~Device()
{

}

int Device::index() const
{
    return i;
}

QString Device::name() const
{
    return n;
}

void Device::setName(const QString &name)
{
    this->n=name;
}

void Device::setSettingsDevice(SettingsDevice *settings)
{
    this->settings=settings;
}
