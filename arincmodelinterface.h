#ifndef ARINCMODELINTERFACE_H
#define ARINCMODELINTERFACE_H
#include "arincparametrobserver.h"
#include <QObject>
struct TimeParametr
{
    double time;
    unsigned int parametr;
    TimeParametr(){}
    TimeParametr(const TimeParametr &p){
        time=p.time;
        parametr=p.parametr;
    }
};
Q_DECLARE_METATYPE(TimeParametr)
class ArincModelInterface{
public:
    virtual void startArinc(int time_milliseconds=10)=0;
    virtual void stopArinc()=0;
    virtual void setTypeParametr(int adress, Parametr::TypeParametr type)=0;
    virtual ArincParametr* getParametr(int adress)=0;
    virtual void readValues(int adress)=0;
    virtual Parametr::TypeParametr TypeParametr(int adress)=0;
    virtual void addArincParametr(int adress)=0;
    virtual void clearParametrs()=0;
    virtual bool hasArincParametr(int adress)=0;
    virtual bool isRunningArinc()=0;
    virtual void registerObserver(ArincParametrObserver *o)=0;
    virtual void removeObserver(ArincParametrObserver *o)=0;
    virtual void notifyObservers()=0;
    virtual ~ArincModelInterface(){}
};
#endif // ARINCMODELINTERFACE_H
