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
    ~ControllerArinc();
    // ControllerInterface interface
public:
    void Start();
    void Stop();
    void addObserveredArincWord(int adress);
    void addDiscrModel(int adress);
    void deleteDiscrModel(int adress);  


    // ControllerInterface interface
public:
    void setNameArincParametr(const QString &name, int adress);
    void setDimensionArincParametr(const QString &dim, int adress);
    void setUnpackConst(double unpack, int adress);
    void setTypeParametr(Parametr::TypeParametr type, int adress);
    void setStateContanier(StateContanier *cont, int adress);
};

#endif // CONTROLLERARINC_H
