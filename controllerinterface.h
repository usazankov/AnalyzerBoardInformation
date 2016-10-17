#ifndef CONTROLLERINTERFACE_H
#define CONTROLLERINTERFACE_H
#include <QString>
namespace dev {
enum TypeDev{PCI429,MPC429};
}
class ControllerInterface{
    virtual void Start();
    virtual void Stop();
    virtual void setConfigurationArincChannel();
};
#endif // CONTROLLERINTERFACE_H
