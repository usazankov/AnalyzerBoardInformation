#include "controllerarinc.h"

ControllerArinc::ControllerArinc(ArincModelInterface *model, MainView *view)
{
    this->model=model;
    this->view=view;
    this->form=view->createMdiChild(this,model);
}

void ControllerArinc::Start()
{
    model->startArinc();
}

void ControllerArinc::Stop()
{
    model->stopArinc();
}

