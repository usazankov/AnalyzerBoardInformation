#include "arincgrafikpanel.h"
#include "ui_arincgrafikpanel.h"

ArincGrafikPanel::ArincGrafikPanel(int adressOfParametr,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ArincGrafikPanel)
{
    ui->setupUi(this);
    adress=adressOfParametr;
    setStyleGrafik();
    graph=ui->customPlot->addGraph();

    graph->setPen(QPen(QColor(0xC0C0C0), 3));
    startTime=QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
    QTimer *timer=new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(upd()));
    timer->start(10);
    time=0;
    cout<<"ArincGrafikPanel in Thread: "<<this->thread()->objectName().toStdString()<<endl;
}

ArincGrafikPanel::~ArincGrafikPanel()
{
    delete ui;
}


void ArincGrafikPanel::setLastData(const QVector<double> &x, const QVector<double> &y)
{

}


void ArincGrafikPanel::setStyleGrafik()
{
    // move bars above graphs and grid below bars:
    ui->customPlot->addLayer("abovemain", ui->customPlot->layer("main"), QCustomPlot::limAbove);
    ui->customPlot->addLayer("belowmain", ui->customPlot->layer("main"), QCustomPlot::limBelow);
    ui->customPlot->xAxis->grid()->setLayer("belowmain");
    ui->customPlot->yAxis->grid()->setLayer("belowmain");
    connect(ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->yAxis2, SLOT(setRange(QCPRange)));
    // set some pens, brushes and backgrounds:
    ui->customPlot->xAxis->setBasePen(QPen(Qt::white, 1));
    ui->customPlot->yAxis->setBasePen(QPen(Qt::white, 1));
    ui->customPlot->xAxis->setTickPen(QPen(Qt::white, 1));
    ui->customPlot->yAxis->setTickPen(QPen(Qt::white, 1));
    ui->customPlot->xAxis->setSubTickPen(QPen(Qt::white, 1));
    ui->customPlot->yAxis->setSubTickPen(QPen(Qt::white, 1));
    ui->customPlot->xAxis->setTickLabelColor(Qt::white);
    ui->customPlot->yAxis->setTickLabelColor(Qt::white);
    ui->customPlot->xAxis->setTickLabelFont(QFont("Helvetica", 11));
    ui->customPlot->yAxis->setTickLabelFont(QFont("Helvetica", 11));
    ui->customPlot->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    ui->customPlot->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    ui->customPlot->xAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    ui->customPlot->yAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    ui->customPlot->xAxis->grid()->setSubGridVisible(true);
    ui->customPlot->yAxis->grid()->setSubGridVisible(true);
    ui->customPlot->xAxis->grid()->setZeroLinePen(Qt::NoPen);
    ui->customPlot->yAxis->grid()->setZeroLinePen(Qt::NoPen);
    ui->customPlot->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    ui->customPlot->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    QLinearGradient plotGradient;
    plotGradient.setStart(0, 0);
    plotGradient.setFinalStop(0, 350);
    plotGradient.setColorAt(0, QColor(49, 54, 59));
    plotGradient.setColorAt(1, QColor(49, 54, 59));
    ui->customPlot->setBackground(plotGradient);
    QLinearGradient axisRectGradient;
    axisRectGradient.setStart(0, 0);
    axisRectGradient.setFinalStop(0, 350);
    axisRectGradient.setColorAt(0, QColor(46,49,52));
    axisRectGradient.setColorAt(1, QColor(24,27,28));
    ui->customPlot->axisRect()->setBackground(axisRectGradient);
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    ui->customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    ui->customPlot->xAxis->setDateTimeFormat("hh:mm:ss");
    ui->customPlot->xAxis->setDateTimeSpec(Qt::TimeSpec::UTC);
}

void ArincGrafikPanel::upd()
{
    ui->customPlot->graph(0)->rescaleAxes();
    //ui->customPlot->xAxis->setRange(time+50, 500, Qt::AlignRight);
    ui->customPlot->replot();
}

void ArincGrafikPanel::update(const QMap<int, ArincParametr *> &map)
{
    graph->addData(QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0-startTime,5);

}

int ArincGrafikPanel::timeToUpdate()
{
    return Ui::default_time_to_update_grafik;
}
