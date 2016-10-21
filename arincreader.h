#ifndef ARINCREADER_H
#define ARINCREADER_H

#include "readingbuffer.h"
#include "parametr_impl.h"
#include "arincmodelinterface.h"
#include <QThread>
#include <QMap>
#include <QTimer>
class ArincReader: public QThread, public ArincModelInterface
{
    Q_OBJECT
public:
    ArincReader(ReadingBuffer<unsigned int*> *arinc);
    void run();
    ~ArincReader();
private:
    ReadingBuffer<unsigned int*> *arinc;
    QMap<int, ArincParametr*> arinc_map;
    QMap<int, ArincParametr*>::iterator iter;
    QVector<ArincParametrObserver*> observers;
    int size;
    int time_step;
    int index;
    // ArincModelInterface interface
    void stopArinc();
    void startArinc(int time_milliseconds=1000);
    void setTypeParametr(int adress, Parametr::TypeParametr type);
    ArincParametr *getParametr(int adress);
    Parametr::TypeParametr TypeParametr(int adress);
    int indexModel();
    void registerObserver(ArincParametrObserver *o);
    void removeObserver(ArincParametrObserver *o);
    void notifyObservers();
    static int count_model;
signals:
    void stopTimer();
private slots:
    void update();

};

#endif // ARINCREADER_H
