#include "grafikmanager.h"

GrafikManager::GrafikManager(MainView *view,QObject *parent) : QObject(parent)
{
    this->view=view;
    connect(this,SIGNAL(signalToCreateGrafikMdiForm(QString,int,int)),view,SLOT(createMdiGrafChild(QString,int,int)));
    connect(this,SIGNAL(createGrafik(int,int,int)),view,SLOT(addGrafikToMdiChild(int,int,int)));
    connect(view,SIGNAL(deleteMdiGraf(int)),this,SLOT(delGrafikMdiForm(int)));
    connect(this,SIGNAL(signalToRemoveObserversGrafik(int)),view,SLOT(deleteObserversMdiForm(int)));
    connect(this,SIGNAL(signalToAddObserversGrafik(int)),view,SLOT(addObserversMdiForm(int)));
    connect(this,SIGNAL(signalToRemoveArincModel(int)),view,SLOT(arincModelIsDeleted(int)));
}

QMap<int,int> GrafikManager::indexsForms_indexsDevice;

int GrafikManager::generateIndex()
{
    QMap<int,int>::const_iterator iter;
    for(iter=indexsForms_indexsDevice.begin();iter!=indexsForms_indexsDevice.end();++iter){
        cout<<"key="<<iter.key()<<" value="<<iter.value()<<endl;
    }
    int i=0;
    while(true){
        if((!indexsForms_indexsDevice.contains(i))&&(!view->containsIndexMdiGraf(i))){
            cout<<"INDEX="<<i<<endl;
            return i;
        }
        ++i;
    }
    return i;
}

void GrafikManager::setOldData(int indexMdiForm, int adress, QVector<TimeParametr> *p,  ArincParametr *arp)
{
    QVector<double> x;
    QVector<double> y;
    QVector<TimeParametr>::const_iterator iter;
    if(arp->Type()==Parametr::ARINC_DEC){
        ArincDecParametr d(*dynamic_cast<ArincDecParametr*>(arp));
        if(d.FormatValue(Parametr::ValueParametr)!="-"&&d.HasValue()){
            for(iter=p->begin();iter!=p->end();++iter){
                x.push_back(iter->time);
                d.setWord(iter->parametr);
                y.push_back(d.Value());
            } 
        }
    }else{
        for(iter=p->begin();iter!=p->end();++iter){
            x.push_back(iter->time);
            y.push_back(0);
        }
    }
    view->grafForm(indexMdiForm)->graphPanel(adress)->setLastData(x,y);
}

void GrafikManager::createGrafikMdiForm(QString title, int index, int indexDevice)
{
    cout<<"indexsFormsGraf Create"<<endl;
    emit signalToCreateGrafikMdiForm(title,index,indexDevice);
    indexsForms_indexsDevice[index]=indexDevice;
    cout<<"indexsFormsGraf.count: "<<indexsForms_indexsDevice.count()<<endl;
}

void GrafikManager::addObserversMdiForm(int indexDevice)
{
    QMap<int,int>::const_iterator iter;
    for(iter=indexsForms_indexsDevice.begin();iter!=indexsForms_indexsDevice.end();++iter){
        if(iter.value()==indexDevice)
            emit signalToAddObserversGrafik(iter.key());
    }
}

void GrafikManager::removeObserversMdiForm(int indexDevice)
{
    QMap<int,int>::const_iterator iter;
    for(iter=indexsForms_indexsDevice.begin();iter!=indexsForms_indexsDevice.end();++iter){
        if(iter.value()==indexDevice)
            emit signalToRemoveObserversGrafik(iter.key());
    }
}

void GrafikManager::clearData()
{
    QMap<int,int>::const_iterator iter;
    for(iter=indexsForms_indexsDevice.begin();iter!=indexsForms_indexsDevice.end();++iter){
        view->grafForm(iter.key())->clearDataGrafiks();
    }
}

QList<int> GrafikManager::indexsMdiForms(int indexDevice)
{
    QList<int> list;
    QMap<int,int>::const_iterator iter;
    for(iter=indexsForms_indexsDevice.begin();iter!=indexsForms_indexsDevice.end();++iter){
        if(iter.value()==indexDevice)
            list.push_back(iter.key());
    }
    return list;
}


void GrafikManager::delGrafikMdiForm(int index)
{
    cout<<"indexsFormsGraf Delete"<<endl;
    if(indexsForms_indexsDevice.contains(index)){
        indexsForms_indexsDevice.remove(index);
    }
    cout<<"indexsFormsGraf.count: "<<indexsForms_indexsDevice.count()<<endl;
}

void GrafikManager::modelIsDeleted(int indexDevice)
{
    QMap<int,int>::const_iterator iter;
    for(iter=indexsForms_indexsDevice.begin();iter!=indexsForms_indexsDevice.end();++iter){
        if(iter.value()==indexDevice)
            emit signalToRemoveArincModel(iter.key());
    }
}

