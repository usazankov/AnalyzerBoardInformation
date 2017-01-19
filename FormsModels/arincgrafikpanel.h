#ifndef ARINCGRAFIKPANEL_H
#define ARINCGRAFIKPANEL_H

#include <QWidget>
#include "arincparametrobserver.h"
#include "FormsModels/QCustomPlot/qcustomplot.h"
namespace Ui {
class ArincGrafikPanel;
const double timeStepToRestructData=10;
const double restructedStep=0.95;//Шаг перерисовки графика (в секундах)
}

class ArincGrafikPanel : public QWidget, public ArincParametrObserver
{
    Q_OBJECT
public:
    explicit ArincGrafikPanel(int adressOfParametr, QWidget *parent = 0);
    ~ArincGrafikPanel();
    void setData(const QVector<double> &x, const QVector<double> &y, Parametr *p);
    void clearData();
    void setTimeStepToUpdate(int timeStepToUpdate);
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
    int timeStepToUpdate;
    double current_value;
    void setStyleGrafik();
    void restructData();
private slots:
    void upd();
public slots:
    void start();
    void stop();
    // ArincParametrObserver interface
public:
    void update(const QMap<int, ArincParametr *> &map, double time);
    int timeToUpdate();
};

#endif // ARINCGRAFIKPANEL_H
