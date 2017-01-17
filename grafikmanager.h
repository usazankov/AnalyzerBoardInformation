#ifndef GRAFIKMANAGER_H
#define GRAFIKMANAGER_H

#include <QObject>
#include "FormsModels/mainview.h"
#include "FormsModels/mdigrafform.h"
class GrafikManager : public QObject
{
    Q_OBJECT
public:
    explicit GrafikManager(MainView *view, QObject *parent = 0);
    int generateIndex();
    void setOldData(int indexMdiForm, int adress, QVector<TimeParametr> *p, ArincParametr *arp);
    void createGrafikMdiForm(QString title,int index,int indexDevice);
    void addObserversMdiForm(int indexDevice);
    void removeObserversMdiForm(int indexDevice);
    void clearData();
    QList<int> indexsMdiForms(int indexDevice);
private:
    MainView *view;
    static QMap<int,int> indexsForms_indexsDevice;
signals:
    void signalToCreateGrafikMdiForm(QString title,int index,int indexDevice);
    void createGrafik(int indexMdiForm, int adress,int indexDevice);
    void signalToRemoveObserversGrafik(int indexMdi);
    void signalToAddObserversGrafik(int indexMdi);
    void signalToRemoveArincModel(int indexDevice);
private slots:
    void delGrafikMdiForm(int index);
    void modelIsDeleted(int indexDevice);
public slots:
};

#endif // GRAFIKMANAGER_H
