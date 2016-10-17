#ifndef CONTROLLERARINC_H
#define CONTROLLERARINC_H
#include "controllerinterface.h"
#include "arincmodelinterface.h"
class ControllerArinc: public ControllerInterface
{
public:
    explicit ControllerArinc(ArincModelInterface *model);
    ArincModelInterface *model;
    // ControllerInterface interface
private:
    void Start();
    void Stop();
    void setConfigurationArincChannel();
};

#endif // CONTROLLERARINC_H
