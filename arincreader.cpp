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

void ArincReader::update()
{
    if(running){
        if(arinc!=Q_NULLPTR){
            double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
            static double lastKeyToArincMap = 0;
            if(key-lastKeyToArincMap>time_step_to_arinc_map){
                cout<<key-lastKeyToArincMap<<endl;
                updateArincMap();
                notifyObservers();
                setWordsToZero();
                lastKeyToArincMap=key;
            }
        }
    }
}

bool ArincReader::hasArincParametr(int adress)
{
    if(arinc_map.contains(adress))return true;
    else return false;
}

bool ArincReader::isRunningArinc()
{
    return timer->isActive();
}

void ArincReader::clearParametrs()
{
    foreach (ArincParametr* p, arinc_map) {
        delete p;
    }
    arinc_map.clear();
}

void ArincReader::setTypeParametr(int adress, Parametr::TypeParametr type)
{
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
}

ArincParametr *ArincReader::getParametr(int adress)
{
    if(arinc_map.contains(adress))
        return arinc_map[adress];
    else return Q_NULLPTR;
}

void ArincReader::registerObserver(ArincParametrObserver *o)
{
    if(!observers.contains(o))
        observers.push_back(o);
}

void ArincReader::removeObserver(ArincParametrObserver *o)
{
    int index=observers.indexOf(o);
    if(index>=0)
        observers.remove(index);
}

void ArincReader::notifyObservers()
{
    for(int i=0;i<observers.size();i++){
        observers[i]->update(arinc_map);
    }
}

Parametr::TypeParametr ArincReader::TypeParametr(int adress)
{
    if(arinc_map.contains(adress))
        return arinc_map[adress]->Type();
    else return Parametr::NoType;
}

void ArincReader::addArincParametr(ArincParametr *arincword)
{
    int adress=arincword->Adress();
    if(!arinc_map.contains(adress)){
        arinc_map[adress]=arincword;
    }
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
    updateArincMap();
    deleteUnregisteredWords();
    notifyObservers();
    arinc->Stop();
    emit stopTimer();
}

ArincReader::~ArincReader()
{
    cout<<"Timer isRuning:"<<timer->isActive()<<endl;
    for(iter=arinc_map.begin();iter!=arinc_map.end();++iter)
        delete iter.value();
    timer->deleteLater();
    cout<<"deleted ArincReader"<<endl;
}

void ArincReader::updateArincMap()
{
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
            cout<<"count="<<arinc_map.count()<<endl;
        }
    }
}

