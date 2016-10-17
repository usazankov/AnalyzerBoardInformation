#include "arincreader.h"

int ArincReader::count_model=0;

ArincReader::ArincReader(ReadingBuffer<unsigned int*> *arinc)
{
    this->arinc=arinc;
    time_step=1000;
    index=count_model++;
}

void ArincReader::update()
{
    if(arinc!=0){
    int adress;
    static int count;
        for(int i=0;i<arinc->sizeOfBuffer();++i){
            adress=(arinc->readBuffer()[i]) & 0xff;
            if(adress!=0){
                if(!arinc_map.contains(adress)){
                    ++count;
                    ArincParametr *word=new ArincParametr(arinc->readBuffer()[i]);
                    arinc_map[adress]=word;
                }else if(arinc_map.contains(adress)){
                    arinc_map[adress]->setWord(arinc->readBuffer()[i]);
                }
                adress=0;
            }
        }
        notifyObservers();
        cout<<"Создано слов:"<<count<<endl;
        cout<<"Всего элементов: "<<arinc_map.size()<<endl;
    }
}

void ArincReader::setTypeParametr(int adress, Parametr::TypeParametr type)
{
    if(arinc_map[adress]->Type()!=type){
    int word = arinc_map[adress]->UnpackValue;
    delete arinc_map[adress];
    switch(type){
        case Parametr::ARINC_DEC:
            arinc_map[adress] = new ArincDecParametr(word);
            break;
        case Parametr::ARINC_DEC_DISCR:
            arinc_map[adress] = new ArincDecDiscrParametr(word);
            break;
        case Parametr::ARINC_DISCR:
            arinc_map[adress] = new ArincDiscrParametr(word);
            break;
        case Parametr::ARINC_PARAM:
            arinc_map[adress] = new ArincParametr(word);
            break;
        default:
            break;
    }
    }
}

ArincParametr *ArincReader::getParametr(int adress)
{
    return arinc_map[adress];
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
        observers[i]->update(&arinc_map);
    }
}

Parametr::TypeParametr ArincReader::TypeParametr(int adress)
{
    return arinc_map[adress]->Type();
}

int ArincReader::indexModel()
{
    return index;
}

void ArincReader::startArinc(int time_milliseconds)
{
    if(!this->isRunning()){
        time_step=time_milliseconds;
        this->start();
    }
}

void ArincReader::stopArinc()
{
    emit stopTimer();
}

void ArincReader::run()
{
    QTimer timer;
    connect(&timer,SIGNAL(timeout()),this,SLOT(update()));
    connect(this,SIGNAL(stopTimer()),&timer,SLOT(stop()));
    timer.start(time_step);
    exec();
}

ArincReader::~ArincReader()
{
    for(iter=arinc_map.begin();iter!=arinc_map.end();++iter)
        delete iter.value();
}
