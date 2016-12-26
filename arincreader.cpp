#include "arincreader.h"

int ArincReader::count_model=0;

ArincReader::ArincReader(ReadingBuffer<unsigned int*> *arinc, QObject *obj):QObject(obj)
{
    this->arinc=arinc;
    time_step_to_arinc_map=0.2;
    timer=new QTimer(this);
    qRegisterMetaType<QVector<int>>();
    qRegisterMetaType<Qt::Orientation>();
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));
    connect(this,SIGNAL(stopTimer()),timer,SLOT(stop()));
    connect(this,SIGNAL(start_Timer(int)),timer,SLOT(start(int)));
}

void ArincReader::lockMutex()
{
    mutex.lock();
}

void ArincReader::unlockMutex()
{
    mutex.unlock();
}

void ArincReader::update()
{
    if(running){
        cout<<"BEGIN Cycle"<<endl;
        if(arinc!=Q_NULLPTR){
            cout<<"arin!=Q_NULLPTR"<<endl;
            double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
            cout<<"CurrentDateTime End"<<endl;
            static double lastKeyToArincMap = 0;
            cout<<"lastKeyToArincMap"<<endl;
            if(key-lastKeyToArincMap>time_step_to_arinc_map){
                cout<<"IF"<<endl;
                updateArincMap();
                notifyObservers();
                setWordsToZero();
                lastKeyToArincMap=key;
                //cout<<"lastKeyArincMap="<<lastKeyToArincMap<<endl;
                cout<<"END Cycle"<<endl;
            }
        }
    }
}

bool ArincReader::hasArincParametr(int adress)
{
    mutex.lock();
    cout<<"LOCKED!"<<endl;
    cout<<"hasArincParametr begin"<<endl;
    if(arinc_map.contains(adress)){
        cout<<"hasArincParametr end"<<endl;
        mutex.unlock();
        cout<<"UNLOCKED!"<<endl<<endl;
        return true;
    }
    else{
        cout<<"hasArincParametr end"<<endl;
        mutex.unlock();
        cout<<"UNLOCKED!"<<endl<<endl;
        return false;
    }

}

bool ArincReader::isRunningArinc()
{
    return timer->isActive();
}

void ArincReader::clearParametrs()
{
    mutex.lock();
    cout<<"LOCKED!"<<endl;
    cout<<"clearParametrs begin"<<endl;
    foreach (ArincParametr* p, arinc_map) {
        cout<<"Cleared "<<p->Adress()<<endl;
        delete p;
    }
    arinc_map.clear();
    cout<<"clearParametrs end"<<endl;
    mutex.unlock();
    cout<<"UNLOCKED!"<<endl<<endl;
}

void ArincReader::setTypeParametr(int adress, Parametr::TypeParametr type)
{
    mutex.lock();
    cout<<"LOCKED!"<<endl;
    cout<<"setTypeParametr begin"<<endl;
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
    cout<<"setTypeParametr end"<<endl;
    mutex.unlock();
    cout<<"UNLOCKED!"<<endl<<endl;
}

ArincParametr *ArincReader::getParametr(int adress)
{
    mutex.lock();
    cout<<"LOCKED!"<<endl;
    cout<<"getParametr begin"<<endl;
    if(arinc_map.contains(adress)){
        cout<<"getParametr end"<<endl;
        mutex.unlock();
        cout<<"UNLOCKED!"<<endl<<endl;
        return arinc_map[adress];
    }
    else{
        cout<<"getParametr end"<<endl;
        mutex.unlock();
        cout<<"UNLOCKED!"<<endl<<endl;
        return Q_NULLPTR;
    }
}

void ArincReader::registerObserver(ArincParametrObserver *o)
{
    mutex.lock();
    cout<<"LOCKED!"<<endl;
    cout<<"registerObserver begin"<<endl;
    if(!observers.contains(o))
        observers.push_back(o);
    cout<<"registerObserver end"<<endl;
    mutex.unlock();
    cout<<"UNLOCKED!"<<endl<<endl;
}

void ArincReader::removeObserver(ArincParametrObserver *o)
{
    mutex.lock();
    cout<<"LOCKED!"<<endl;
    cout<<"removeObserver begin"<<endl;
    int index=observers.indexOf(o);
    if(index>=0){
        observers.remove(index);
    }
    cout<<"addArincParametr end"<<endl;
    mutex.unlock();
    cout<<"UNLOCKED!"<<endl<<endl;
}

void ArincReader::notifyObservers()
{   mutex.lock();
    cout<<"notifyObservers begin"<<endl;
    for(int i=0;i<observers.size();i++){
        observers[i]->update(arinc_map);
    }
    mutex.unlock();
    cout<<"notifyObservers end"<<endl;
}

Parametr::TypeParametr ArincReader::TypeParametr(int adress)
{
    mutex.lock();
    cout<<"LOCKED!"<<endl;
    cout<<"TypeParametr begin"<<endl;
    if(arinc_map.contains(adress))
        return arinc_map[adress]->Type();
    else return Parametr::NoType;
    cout<<"addArincParametr end"<<endl;
    mutex.unlock();
    cout<<"UNLOCKED!"<<endl<<endl;
}

void ArincReader::addArincParametr(ArincParametr *arincword)
{
    mutex.lock();
    cout<<"LOCKED!"<<endl;
    cout<<"addArincParametr begin"<<endl;
    int adress=arincword->Adress();
    if(!arinc_map.contains(adress)){
        arinc_map[adress]=arincword;
    }
    cout<<"addArincParametr end"<<endl;
    mutex.unlock();
    cout<<"UNLOCKED!"<<endl<<endl;
}


void ArincReader::startArinc(int time_milliseconds)
{
    running=1;
    arinc->Start();
    emit start_Timer(time_milliseconds);
}

void ArincReader::stopArinc()
{
    running=0;
    arinc->Stop();
    emit stopTimer();
    updateArincMap();
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

void ArincReader::updateArincMap()
{
    cout<<"PreMutex!"<<endl;
    mutex.lock();
    cout<<"LOCKED!"<<endl;
    cout<<"updateArincMap begin"<<endl;
    int adress;
    for(int i=0;i<arinc->sizeOfBuffer();++i){
        adress=(arinc->readBuffer()[i]) & 0xff;
        if(adress!=0){
            if(!arinc_map.contains(adress)){
                ArincParametr *word=new ArincParametr(arinc->readBuffer()[i]);
                word->setHasValue(true);
                arinc_map[adress]=word;
            }else if(arinc_map.contains(adress)){
                arinc_map[adress]->setWord(arinc->readBuffer()[i]);
                arinc_map[adress]->setHasValue(true);
            }
            adress=0;
        }
    }
    cout<<"updateArincMap end"<<endl;
    mutex.unlock();
    cout<<"UNLOCKED!"<<endl<<endl;

}

void ArincReader::setWordsToZero()
{
    cout<<"setWordsToZero begin"<<endl;
    foreach (ArincParametr *word, arinc_map) {
        if(word->HasValue())
            word->setWord(0);
            word->setHasValue(false);
    }
    cout<<"setWordsToZero end"<<endl;
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

