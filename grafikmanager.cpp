#include "grafikmanager.h"

GrafikManager::GrafikManager(MainView *view,QObject *parent) : QObject(parent)
{
    this->view=view;
    connect(this,SIGNAL(createGrafikMdiForm(QString,int)),view,SLOT(createMdiGrafChild(QString,int)));
    connect(this,SIGNAL(createGrafik(int,int)),view,SLOT(addGrafikToMdiChild(int,int)));
    connect(view,SIGNAL(deleteMdiGraf(int)),this,SLOT(delMdiForm(int)));
}

QMap<int, QString> GrafikManager::titleForms;

int GrafikManager::generateIndex()
{
    int i=0;
    while(true){
        if(!titleForms.contains(i)){
            cout<<"i="<<i<<endl;
            return i;
        }
        ++i;
    }
    cout<<"i="<<i<<endl;
    return i;
}

void GrafikManager::delMdiForm(int index)
{
    if(titleForms.contains(index))
        titleForms.remove(index);
}
