#ifndef CONTROLLERINTERFACE_H
#define CONTROLLERINTERFACE_H
#include <QString>
#include "parametr.h"
#include "states.h"

class ControllerInterface{
public:
    virtual void Start(int time_milliseconds=0)=0;
    virtual void Stop()=0;
    virtual void addObserveredArincWord(int adress)=0;
    virtual void setNameArincParametr(const QString &name,int adress)=0;
    virtual void setDimensionArincParametr(const QString &dim,int adress)=0;
    virtual void setUnpackConst(double unpack,int adress)=0;
    virtual void setTypeParametr(Parametr::TypeParametr type,int adress)=0;
    virtual void setRegisteredParametr(bool flag,int adress)=0;
    virtual void clearArincParametrs()=0;
    virtual void addDiscrModel(int adress)=0;
    virtual void deleteDiscrModel(int adress)=0;
    virtual void deleteAllDiscrModel()=0;
    virtual void buildDiscrsModel()=0;
    virtual QString TitleForm()const=0;
    virtual void setStateContanier(StateContanier *cont,int adress)=0;
    virtual void update()=0;
    virtual ~ControllerInterface(){}
};
#endif // CONTROLLERINTERFACE_H
