#ifndef CONTROLLERINTERFACE_H
#define CONTROLLERINTERFACE_H
#include <QString>
namespace dev {
enum TypeDev{PCI429,MPC429};
}
class ControllerInterface{
public:
    virtual void Start()=0;
    virtual void Stop()=0;
    virtual void setConfigurationArincChannel()=0;
};
#endif // CONTROLLERINTERFACE_H
