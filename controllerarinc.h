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
    explicit ControllerArinc(MainView *view, ArincModelInterface *model, int index);

    ~ControllerArinc();
    // ControllerInterface interface
private:
    ArincModelInterface *model;
    //MainView *view;
    MdiForm *form;
    int index_contr;
public:
    void Start();
    void Stop();
    void addObserveredArincWord(int adress);
    void addDiscrModel(int adress);
    void deleteDiscrModel(int adress);  
    void setTitleForm(const QString &name);
    QString TitleForm()const;
    int index();
    MdiForm* getMdiForm();
    // ControllerInterface interface
public:
    void setNameArincParametr(const QString &name, int adress);
    void setDimensionArincParametr(const QString &dim, int adress);
    void setUnpackConst(double unpack, int adress);
    void setTypeParametr(Parametr::TypeParametr type, int adress);
    void setStateContanier(StateContanier *cont, int adress);

};

#endif // CONTROLLERARINC_H
