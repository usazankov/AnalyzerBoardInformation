#include "arincreader.h"

int ArincReader::count_model=0;

ArincReader::ArincReader(ReadingBuffer<unsigned int*> *arinc, QObject *obj):QObject(obj)
{
    this->arinc=arinc;
    time_step_to_arinc_map=0.01;
    time_step_to_zero=0.1;
    time_step_to_write_file=0.1;
    time_step_to_flush=1.0;
    timer=new QTimer(this);
    qRegisterMetaType<QVector<int>>();
    qRegisterMetaType<Qt::Orientation>();
    qRegisterMetaType<QVector<TimeParametr>>();
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));
    connect(this,SIGNAL(stopTimer()),timer,SLOT(stop()));
    connect(this,SIGNAL(start_Timer(int)),timer,SLOT(start(int)));
    manager = new LogsManager(obj);
    connect(manager->reader,SIGNAL(data(QVector<TimeParametr>*)),this,SLOT(getLogsData(QVector<TimeParametr>*)));
}

void ArincReader::update()
{
    if(running){
        if(arinc!=Q_NULLPTR){
            key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
            static double lastKeyToArincMap = 0;
            static double lastKeyToFlush=0;
            static double lastKeyToZero=0;
            static double lastKeyToWrite=0;
            if(key-lastKeyToArincMap>=time_step_to_arinc_map){
                //cout<<"Current_time="<<key-start_time<<endl;
                if(writeToFile&&(key-lastKeyToWrite)>=time_step_to_write_file){
                    manager->writeTime(key-start_time);
                    flagToWrite=1;
                    lastKeyToWrite=key;
                }
                process();
                notifyObservers();
                lastKeyToArincMap=key;
            }
            if(key-lastKeyToZero>=time_step_to_zero){
                setWordsToZero();
                lastKeyToZero=key;
            }
            if(key-lastKeyToFlush>=time_step_to_flush){
                manager->closeFile();
                manager->openFile();
                lastKeyToFlush=key;
            }
        }
    }
}

void ArincReader::getLogsData(QVector<TimeParametr> *p)
{
    emit sendLogsData(p);
}

bool ArincReader::hasArincParametr(int adress)
{
    mutex.lock();
    //cout<<"LOCKED!"<<endl;
    //cout<<"hasArincParametr begin"<<endl;
    if(arinc_map.contains(adress)){
        cout<<"hasArincParametr end"<<endl;
        mutex.unlock();
        cout<<"UNLOCKED!"<<endl<<endl;
        return true;
    }
    else{
        //cout<<"hasArincParametr end"<<endl;
        mutex.unlock();
        //cout<<"UNLOCKED!"<<endl<<endl;
        return false;
    }

}

bool ArincReader::isRunningArinc()
{
    return running;
}

void ArincReader::clearParametrs()
{
    mutex.lock();
    //cout<<"LOCKED!"<<endl;
    //cout<<"clearParametrs begin"<<endl;
    foreach (ArincParametr* p, arinc_map) {
        //cout<<"Cleared "<<p->Adress()<<endl;
        delete p;
    }
    arinc_map.clear();
    //cout<<"clearParametrs end"<<endl;
    mutex.unlock();
    //cout<<"UNLOCKED!"<<endl<<endl;
}

void ArincReader::readValues(int adress)
{
    manager->read(adress);
}

void ArincReader::setTypeParametr(int adress, Parametr::TypeParametr type)
{
    mutex.lock();
    //cout<<"LOCKED!"<<endl;
    //cout<<"setTypeParametr begin"<<endl;
    if(arinc_map.contains(adress))
    if(arinc_map[adress]->Type()!=type){
        int word = arinc_map[adress]->UnpackWord();
        QString name = arinc_map[adress]->Name();
        QString dimension = arinc_map[adress]->Dimension();
        delete arinc_map[adress];
        switch(type){
            case Parametr::ARINC_DEC:
                arinc_map[adress] = new ArincDecParametr(word,name,dimension);
                break;
            case Parametr::ARINC_DEC_DISCR:
                arinc_map[adress] = new ArincDecDiscrParametr(word,name);
                break;
            case Parametr::ARINC_DISCR:
                arinc_map[adress] = new ArincDiscrParametr(word,name);
                break;
            case Parametr::ARINC_PARAM:
                arinc_map[adress] = new ArincParametr(word,name,dimension);
                break;
            default:
                break;
        }
    }
    //cout<<"setTypeParametr end"<<endl;
    mutex.unlock();
    //cout<<"UNLOCKED!"<<endl<<endl;
}

ArincParametr *ArincReader::getParametr(int adress)
{
    mutex.lock();
    //cout<<"LOCKED!"<<endl;
    //cout<<"getParametr begin"<<endl;
    if(arinc_map.contains(adress)){
        //cout<<"getParametr end"<<endl;
        mutex.unlock();
        //cout<<"UNLOCKED!"<<endl<<endl;
        return arinc_map[adress];
    }
    else{
        //cout<<"getParametr end"<<endl;
        mutex.unlock();
        //cout<<"UNLOCKED!"<<endl<<endl;
        return Q_NULLPTR;
    }
}

void ArincReader::registerObserver(ArincParametrObserver *o)
{
    mutex.lock();
    //cout<<"LOCKED!"<<endl;
    //cout<<"registerObserver begin"<<endl;
    if(!observers.contains(o)){
        //cout<<"observer REGISTERED"<<endl;
        observers.push_back(o);
        lastKeysToNotify.push_back(0.0);
    }
    //cout<<"registerObserver end"<<endl;
    //cout<<"countObservers: "<<observers.count()<<endl;
    mutex.unlock();
    //cout<<"UNLOCKED!"<<endl<<endl;
}

void ArincReader::removeObserver(ArincParametrObserver *o)
{
    mutex.lock();
    //cout<<"LOCKED!"<<endl;
    //cout<<"removeObserver begin"<<endl;
    int index=observers.indexOf(o);
    if(index>=0){
        observers.remove(index);
    }
    //cout<<"addArincParametr end"<<endl;
    //cout<<"countObservers: "<<observers.count()<<endl;
    mutex.unlock();
    //cout<<"UNLOCKED!"<<endl<<endl;

}

void ArincReader::notifyObservers()
{
    mutex.lock();
    for(int i=0;i<observers.size();i++){
        if((key-lastKeysToNotify[i]>=observers[i]->timeToUpdate()/1000.0)||!isRunningArinc()){
            observers[i]->update(arinc_map);
            lastKeysToNotify[i]=key;
        }
    }
    mutex.unlock();

}

Parametr::TypeParametr ArincReader::TypeParametr(int adress)
{
    mutex.lock();
    //cout<<"LOCKED!"<<endl;
    //cout<<"TypeParametr begin"<<endl;
    if(arinc_map.contains(adress))
        return arinc_map[adress]->Type();
    else return Parametr::NoType;
    //cout<<"addArincParametr end"<<endl;
    mutex.unlock();
    //cout<<"UNLOCKED!"<<endl<<endl;
}

void ArincReader::addArincParametr(int adress)
{
    mutex.lock();
    //cout<<"LOCKED!"<<endl;
    //cout<<"addArincParametr begin"<<endl;
    if(!arinc_map.contains(adress)){
        arinc_map[adress]=new ArincParametr(adress);
    }
    //cout<<"addArincParametr end"<<endl;
    mutex.unlock();
    //cout<<"UNLOCKED!"<<endl<<endl;
}

void ArincReader::startArinc(int time_milliseconds)
{
    running=1;
    writeToFile=1;
    arinc->Start();
    start_time=QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
    manager->openFile();
    manager->writeSizeBuf(arinc->sizeOfBuffer());
    emit start_Timer(time_milliseconds);
}

void ArincReader::stopArinc()
{
    running=0;
    writeToFile=0;
    arinc->Stop();
    emit stopTimer();
    process();
    manager->closeFile();
    deleteUnregisteredWords();
    notifyObservers();
}

ArincReader::~ArincReader()
{
    foreach (ArincParametr* p, arinc_map) {
        arinc_map.remove(p->Adress());
        delete p;
    }
    timer->deleteLater();
}

void ArincReader::process()
{
    mutex.lock();
    int adress;
    unsigned int temp;
    for(int i=0;i<arinc->sizeOfBuffer();++i){
        temp=arinc->readBuffer()[i];
        if(writeToFile&&flagToWrite){
            manager->writeWord(temp);
        }
        adress=(temp) & 0xff;
        if(adress!=0){
            if(!arinc_map.contains(adress)){
                ArincParametr *word=new ArincParametr(temp);
                word->setHasValue(true);
                arinc_map[adress]=word;
            }else if(arinc_map.contains(adress)){
                arinc_map[adress]->setWord(temp);
                arinc_map[adress]->setHasValue(true);
            }
            adress=0;
        }
    }
    flagToWrite=0;
    mutex.unlock();
}

void ArincReader::setWordsToZero()
{
    foreach (ArincParametr *word, arinc_map) {
        if(word->HasValue())
            word->setWord(0);
            word->setHasValue(false);
    }
}

void ArincReader::deleteUnregisteredWords()
{
    foreach (ArincParametr *word, arinc_map) {
        if(!word->registered()){
            arinc_map.remove(word->Adress());
            delete word;
        }
    }
}

