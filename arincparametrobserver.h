#ifndef PARAMETROBSERVER_H
#define PARAMETROBSERVER_H
#include <QMap>
#include "UnpackingArinc/parametr_impl.h"

class ArincParametrObserver{
public:
    virtual void update(const QMap<int, ArincParametr*> &map, double time)=0;
    virtual int timeToUpdate()=0;//Период обновления в миллисекундах
};
#endif // PARAMETROBSERVER_H
