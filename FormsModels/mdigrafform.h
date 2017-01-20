#ifndef MDIGRAFFORM_H
#define MDIGRAFFORM_H

#include <QWidget>
#include "arincmodelinterface.h"
#include "arincreader.h"
#include <QScopedPointer>
#include "FormsModels/arincgrafikpanel.h"
namespace Ui {
class MdiGrafForm;
}

class MdiGrafForm : public QWidget
{
    Q_OBJECT

public:
    explicit MdiGrafForm(QString title,int index, QWidget *parent = 0);
    ArincGrafikPanel* graphPanel(int adress);
    QMap<int,ArincGrafikPanel*> *arincGrafikPanels();
    int index()const;
    void setModel(ArincModelInterface* model);
    void clearDataGrafiks();
    int countObservers();
    void startPlotting();
    void stopPlotting();

    static void setDefaultTimeStepToUpdate(int timeStep);
    bool isRunningPlot()const;
    virtual ~MdiGrafForm();
    void resetModel();
signals:
    void deletedGrafForm(int index);
    void signalToStartPlotting(int milliseconds);
    void signalToStopPlotting();
    void setTimeStepToUpdate(int timeStep);
public slots:
    void addGrafik(int adress);
    void delObservers();
    void addObservers();
private:
    Ui::MdiGrafForm *ui;
    QString title;
    int count_Observers;
    int i;
    static int timeStepToUpdate;
    bool runningPlot;
    ArincModelInterface* model;
    QMap<int,ArincGrafikPanel*> grafiks;
};

#endif // MDIGRAFFORM_H
