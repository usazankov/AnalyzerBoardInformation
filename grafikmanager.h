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
private:
    MainView *view;
    static QMap<int, QString> titleForms;
signals:
    void createGrafikMdiForm(QString title,int index);
    void createGrafik(int indexMdiForm, int adress);
private slots:
    void delMdiForm(int index);
public slots:
};

#endif // GRAFIKMANAGER_H
