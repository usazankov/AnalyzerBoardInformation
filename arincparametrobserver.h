#ifndef PARAMETROBSERVER_H
#define PARAMETROBSERVER_H
#include <QMap>
#include "parametr_impl.h"
class ArincParametrObserver{
public:
    virtual void update(const QMap<int, ArincParametr*> &map)=0;
};
#endif // PARAMETROBSERVER_H
