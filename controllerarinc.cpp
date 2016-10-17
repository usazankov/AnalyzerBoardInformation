#include "controllerarinc.h"

ControllerArinc::ControllerArinc(ArincModelInterface *model)
{

}

void ControllerArinc::Start()
{
    model->startArinc();
}

void ControllerArinc::Stop()
{
    model->stopArinc();
}

void ControllerArinc::setConfigurationArincChannel()
{

}
