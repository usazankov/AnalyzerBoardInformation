#ifndef CONTROLLERARINC_H
#define CONTROLLERARINC_H
#include "mainview.h"
#include "controllerinterface.h"
#include "arincmodelinterface.h"
#include "mdiform.h"
#include <iostream>
using namespace std;
class ControllerArinc: public ControllerInterface
{

public:
    explicit ControllerArinc(MdiForm *form, ArincModelInterface *model);
    ~ControllerArinc();
    // ControllerInterface interface
private:
    ArincModelInterface *model;
    //MainView *view;
    MdiForm *form;
    QList<int> discrs_models;
public:
    void Start(int time_milliseconds);
    void Stop();
    void addObserveredArincWord(int adress);
    void addDiscrModel(int adress);
    void deleteDiscrModel(int adress);  
    void setTitleForm(const QString &name);
    void deleteAllDiscrModel();
    QString TitleForm()const;
    MdiForm* getMdiForm();
    // ControllerInterface interface
public:
    void setNameArincParametr(const QString &name, int adress);
    void setDimensionArincParametr(const QString &dim, int adress);
    void setUnpackConst(double unpack, int adress);
    void setTypeParametr(Parametr::TypeParametr type, int adress);
    void setStateContanier(StateContanier *cont, int adress);
    void clearArincParametrs();


    // ControllerInterface interface
public:
    void update();

    // ControllerInterface interface
public:
    void setRegisteredParametr(bool flag, int adress);
};

#endif // CONTROLLERARINC_H
