#ifndef MDIGRAFFORM_H
#define MDIGRAFFORM_H

#include <QWidget>
#include "arincmodelinterface.h"
#include "arincreader.h"
#include <QScopedPointer>
#include "FormsModels/arincgrafikpanel.h"
namespace Ui {
class MdiGrafForm;
const int DefaultTimeStepToUpdateGrafiks=10;
}

class MdiGrafForm : public QWidget
{
    Q_OBJECT

public:
    explicit MdiGrafForm(QString title,int index, QWidget *parent = 0);
    ArincGrafikPanel* graphPanel(int adress);
    int index()const;
    void setModel(ArincModelInterface* model);
    void clearDataGrafiks();
    int countObservers();
    void startPlotting();
    void stopPlotting();
    void setTimeStepToUpdate(int timeStep);
    void setDefaultTimeStepToUpdate(int timeStep);
    void applyDefaultTimeStepToUpdate();
    bool isRunningPlot()const;
    virtual ~MdiGrafForm();
    void resetModel();
signals:
    void deletedGrafForm(int index);
    void signalToStartPlotting();
    void signalToStopPlotting();
public slots:
    void addGrafik(int adress);
    void delObservers();
    void addObservers();
private:
    Ui::MdiGrafForm *ui;
    QString title;
    int count_Observers;
    int i;
    int timeStepToUpdate;
    bool runningPlot;
    ArincModelInterface* model;
    QMap<int,ArincGrafikPanel*> grafiks;
};

#endif // MDIGRAFFORM_H
