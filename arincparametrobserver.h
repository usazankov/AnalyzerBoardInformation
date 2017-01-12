#ifndef PARAMETROBSERVER_H
#define PARAMETROBSERVER_H
#include <QMap>
#include "UnpackingArinc/parametr_impl.h"
namespace Ui {
const int default_time_to_update_tables=100;
const int default_time_to_update_grafik=10;
}
class ArincParametrObserver{
public:
    virtual void update(const QMap<int, ArincParametr*> &map)=0;
    virtual int timeToUpdate()=0;//Период обновления в миллисекундах
};
#endif // PARAMETROBSERVER_H
