#ifndef CONTROLLERARINC_H
#define CONTROLLERARINC_H
#include "controllerinterface.h"
#include "arincmodelinterface.h"
#include "mdiform.h"
#include "mainview.h"
class ControllerArinc: public ControllerInterface
{
public:
    explicit ControllerArinc(ArincModelInterface *model, MainView *view);
    ArincModelInterface *model;
    MainView *view;
    MdiForm *form;
    // ControllerInterface interface
private:
    void Start();
    void Stop();
};

#endif // CONTROLLERARINC_H
