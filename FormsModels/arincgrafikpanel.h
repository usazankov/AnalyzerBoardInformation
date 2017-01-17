#ifndef ARINCGRAFIKPANEL_H
#define ARINCGRAFIKPANEL_H

#include <QWidget>
#include "arincparametrobserver.h"
#include "FormsModels/QCustomPlot/qcustomplot.h"
namespace Ui {
class ArincGrafikPanel;
}

class ArincGrafikPanel : public QWidget, public ArincParametrObserver
{
    Q_OBJECT
public:
    explicit ArincGrafikPanel(int adressOfParametr, QWidget *parent = 0);
    ~ArincGrafikPanel();
    void setLastData(const QVector<double> &x, const QVector<double> &y);
    void clearData();
    void setTimeStepToUpdate(int timeStepToUpdate);
    static double startTime;
    static double current_time;
private:
    Ui::ArincGrafikPanel *ui;
    QCPGraph *graph;
    QTimer *timer;
    int adress;
    bool loadedLastData;
    int timeStepToUpdate;
    double current_value;
    void setStyleGrafik();
private slots:
    void upd();
public slots:
    void start();
    void stop();
    // ArincParametrObserver interface
public:
    void update(const QMap<int, ArincParametr *> &map);
    int timeToUpdate();
};

#endif // ARINCGRAFIKPANEL_H
