#ifndef PARAMETROBSERVER_H
#define PARAMETROBSERVER_H
#include <QMap>
#include "parametr_impl.h"
class ArincParametrObserver{
public:
    virtual void update(QMap<int, ArincParametr*> *map);
};
#endif // PARAMETROBSERVER_H
