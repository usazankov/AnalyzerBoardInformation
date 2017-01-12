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
private:
    Ui::ArincGrafikPanel *ui;
    QCPGraph *graph;
    int adress;
    bool loadedLastData;
    double startTime;
    double time;
    void setStyleGrafik();
private slots:
    void upd();
    // ArincParametrObserver interface
public:
    void update(const QMap<int, ArincParametr *> &map);
    int timeToUpdate();
};

#endif // ARINCGRAFIKPANEL_H
