#ifndef ARINCGRAFIKPANEL_H
#define ARINCGRAFIKPANEL_H

#include <QWidget>
#include "arincparametrobserver.h"
#include "FormsModels/QCustomPlot/qcustomplot.h"
namespace Ui {
class ArincGrafikPanel;
const int DefaultTimeStepToUpdateGrafiks=10;
const double DefaultTimeStepToRestructData=600;
const double DefaultRestructedStep=0.95;//Шаг перерисовки графика (в секундах)
const bool DefaultRestruct=false;
}

class ArincGrafikPanel : public QWidget, public ArincParametrObserver
{
    Q_OBJECT
public:
    explicit ArincGrafikPanel(int adressOfParametr, QWidget *parent = 0);
    ~ArincGrafikPanel();
    void setData(const QVector<double> &x, const QVector<double> &y, Parametr *p);
    void clearData();
    static void setRestructData(bool flag);
    static void setTimeStepToUpdate(int timeStepToUpdate);
    static void setStepToRestructData(double seconds);
    static void setRestructedStep(double seconds);
    static double startTime;
    double current_time;
private:
    Ui::ArincGrafikPanel *ui;
    QCPGraph *graph;
    QTimer *timer;
    QTimer *timer_restruct;
    int adress;
    bool loadedLastData;
    QMap<double, QCPData>::iterator last_restruct_data;
    double beginAddedDataTime;
    double lastKeyToRestructData;
    static int timeStepToUpdate;
    double current_value;
    static double timeStepToRestructData;
    static double restructedStep;
    static bool restruct;
    void setStyleGrafik();
    void restructData();
private slots:
    void upd();
public slots:
    void start(int milliseconds);
    void stop();
    void setTimeStepToReplot(int timeStep);
    // ArincParametrObserver interface
public:
    void update(const QMap<int, ArincParametr *> &map, double time);
    int timeToUpdate();
signals:

};

#endif // ARINCGRAFIKPANEL_H
