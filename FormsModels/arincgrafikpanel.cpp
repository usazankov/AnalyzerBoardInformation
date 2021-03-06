#include "arincgrafikpanel.h"
#include "ui_arincgrafikpanel.h"

int ArincGrafikPanel::timeStepToUpdate=Ui::DefaultTimeStepToUpdateGrafiks;
double ArincGrafikPanel::timeStepToRestructData=Ui::DefaultTimeStepToRestructData;
double ArincGrafikPanel::restructedStep=Ui::DefaultRestructedStep;
bool ArincGrafikPanel::restruct=Ui::DefaultRestruct;
ArincGrafikPanel::ArincGrafikPanel(int adressOfParametr,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ArincGrafikPanel)
{
    ui->setupUi(this);
    adress=adressOfParametr;
    setStyleGrafik();
    graph=ui->customPlot->addGraph();
    graph->setPen(QPen(QColor(0xC0C0C0), 1));
    timer=new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(upd()));
    timeStepToUpdate=10;
    beginAddedDataTime=0;
    //graph->addData(0,0);
    last_restruct_data=graph->data()->begin();
}
double ArincGrafikPanel::startTime;
ArincGrafikPanel::~ArincGrafikPanel()
{
    timer->stop();
    delete ui;
    delete timer;
}

void ArincGrafikPanel::setData(const QVector<double> &x, const QVector<double> &y, Parametr* p)
{
    cout<<"SettingLastData"<<endl;
    cout<<"cout time"<<x.count()<<endl;
    //graph->addData(0,0);
    graph->addData(x,y);
    ui->customPlot->yAxis->setLabel(p->Name()+", "+p->Dimension());
    ui->customPlot->xAxis->setLabel("Время");
    if(!x.empty()){
        beginAddedDataTime=x.last();
        last_restruct_data=graph->data()->end();
        --last_restruct_data;
        cout<<"!x.empty"<<endl;
    }else{
        beginAddedDataTime=0;
        last_restruct_data=graph->data()->begin();
        cout<<"last_restruct_data.begin"<<endl;
    }

}

void ArincGrafikPanel::clearData()
{
    graph->clearData();
    //graph->addData(0,0);
    last_restruct_data=graph->data()->begin();
    lastKeyToRestructData=0;
}

void ArincGrafikPanel::setRestructData(bool flag)
{
    restruct=flag;
}

void ArincGrafikPanel::setTimeStepToUpdate(int timeStepToUpdate)
{
    ArincGrafikPanel::timeStepToUpdate=timeStepToUpdate;
}

void ArincGrafikPanel::setStepToRestructData(double seconds)
{
    timeStepToRestructData=seconds;
}

void ArincGrafikPanel::setRestructedStep(double seconds)
{
    restructedStep=seconds;
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
    ui->customPlot->yAxis->setLabelColor(Qt::white);
    ui->customPlot->xAxis->setLabelColor(Qt::white);
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

void ArincGrafikPanel::restructData()
{
//    for (auto it = graph->data()->begin(); it != graph->data()->end();++it){
//        cout<<"before key="<<it.key()<<endl;
//    }
    double delta=restructedStep;
    cout<<"begin="<<last_restruct_data.key()<<endl;
    QMap<double, QCPData>::iterator it_p = last_restruct_data;
    QMap<double, QCPData>::iterator it;
    if(last_restruct_data==graph->data()->begin()){
        it=graph->data()->begin();
        ++it;
        cout<<"begin"<<endl;
    }else{
        it = graph->data()->find(last_restruct_data.key());
        ++it;
    }
    if(it_p!=graph->data()->end()&&it!=graph->data()->end()){
    for (; it != graph->data()->end();){
        if(it.key()-it_p.key()<delta&&it.key()!=0){
            graph->data()->erase(it++);
        }else{
            it_p=it;
            ++it;
        }
    }
    }else{
        cout<<"iters is end"<<endl;
    }
    double lastData=graph->data()->last().key;
    cout<<"end="<<lastData<<endl;
    for (auto it = graph->data()->begin(); it != graph->data()->end();++it){
        cout<<"key="<<it.key()<<endl;
    }
    cout<<"count="<<graph->data()->count()<<endl;
    last_restruct_data=graph->data()->end();
    --last_restruct_data;
    cout<<"Restructed Graphiks 0"<<oct<<adress<<dec<<endl;
}

void ArincGrafikPanel::upd()
{
    ui->customPlot->graph(0)->rescaleKeyAxis();
    ui->customPlot->replot();
    //ui->customPlot->xAxis->setRange(QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0-startTime+0.5, 10, Qt::AlignRight);
    try{
    if(current_time-lastKeyToRestructData>=timeStepToRestructData&&restruct){
        cout<<"count.graph"<<graph->data()->count()<<endl;
            restructData();
            lastKeyToRestructData=current_time;
        }
    }catch(...){
        std::cout << "Allocation failed: " << '\n';
    }
}

void ArincGrafikPanel::start(int milliseconds)
{
    if(!timer->isActive())
        timer->start(milliseconds);
}

void ArincGrafikPanel::stop()
{
    if(timer->isActive())
        timer->stop();
}

void ArincGrafikPanel::setTimeStepToReplot(int timeStep)
{
    timer->setInterval(timeStep);
}

void ArincGrafikPanel::update(const QMap<int, ArincParametr *> &map, double time)
{
    if(map.contains(adress)){
        if(map[adress]->FormatValue(Parametr::ValueParametr)!="-")
            graph->addData(time,map[adress]->FormatValue(Parametr::ValueParametr).toDouble());
        else graph->addData(time,0);
    }else graph->addData(time,0);
    current_time=time;
}

int ArincGrafikPanel::timeToUpdate()
{
    return timeStepToUpdate;
}
