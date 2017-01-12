#ifndef ARINCREADER_H
#define ARINCREADER_H

#include "ArincBoards/arincintefaces.h"
#include "arincmodelinterface.h"
#include "UnpackingArinc/parametr_impl.h"
#include "logsmanager.h"
#include <QVector>
#include <QThread>
#include <QMap>
#include <QTimer>
#include <QDateTime>
#include <QMutex>
class ArincReader:public QObject, public ArincModelInterface
{
    Q_OBJECT
public:
    ArincReader(ReadingBuffer<unsigned int*> *arinc,QObject *obj=0);
    ~ArincReader();
private:
    ReadingBuffer<unsigned int*> *arinc;
    QMap<int, ArincParametr*> arinc_map;
    QMap<int, ArincParametr*>::iterator iter;
    QVector<ArincParametrObserver*> observers;
    QVector<double> lastKeysToNotify;
    QMutex	mutex;
    LogsManager *manager;
    double key;
    int size;
    double start_time;
    bool running;
    bool writeToFile;
    bool flagToWrite;
    double time_step_to_arinc_map;
    double time_step_to_zero;
    double time_step_to_flush;
    double time_step_to_write_file;
    void process();
    void setWordsToZero();
    void deleteUnregisteredWords();
    // ArincModelInterface interface
    void stopArinc();
    void startArinc(int time_milliseconds);
    void setTypeParametr(int adress, Parametr::TypeParametr type);
    ArincParametr *getParametr(int adress);
    Parametr::TypeParametr TypeParametr(int adress);
    void addArincParametr(int adress);
    void registerObserver(ArincParametrObserver *o);
    void removeObserver(ArincParametrObserver *o);
    void notifyObservers();
    static int count_model;
    QTimer *timer;
private slots:
    void update();
signals:
    void stopTimer();
    void start_Timer(int);
    void sendLogsData(QVector<TimeParametr> *p);
public slots:
    void getLogsData(QVector<TimeParametr> *p);
    // ArincModelInterface interface
public:
    bool hasArincParametr(int adress);

    // ArincModelInterface interface
public:
    bool isRunningArinc();

    // ArincModelInterface interface
public:
    void clearParametrs();


    // ArincModelInterface interface
public:
    void readValues(int adress);
};

#endif // ARINCREADER_H
