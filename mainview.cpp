#include "mainview.h"
#include "ui_mainview.h"

MainView::MainView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainView)
{
    ui->setupUi(this);
    ui->mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->mdiArea->setViewMode(QMdiArea::TabbedView);
    //ui->mdiArea->setTabsClosable(true);
    ui->mdiArea->setTabsMovable(true);
    ui->mdiArea->setDocumentMode(true);
    createToolBars();
}

MainView::~MainView()
{
    delete ui;
}

void MainView::createToolBars()
{
    fileToolBar=this->addToolBar(tr("File"));
    fileToolBar->addAction(ui->action_open);
    fileToolBar->addAction(ui->action_save);

    deviceToolBar=this->addToolBar(tr("Device"));
    deviceToolBar->addAction(ui->action_add_device);
    deviceToolBar->addAction(ui->action_del_device);
}

MdiForm *MainView::activeMdiChild()
{
    if (QMdiSubWindow *activeSubWindow = ui->mdiArea->activeSubWindow())
        return qobject_cast<MdiForm *>(activeSubWindow->widget());
    return 0;
}

QMdiSubWindow *MainView::findMdiChild(const QString &fileName)
{

}

void MainView::setStyle()
{

}

void MainView::setActiveSubWindow(QWidget *window)
{
    if (!window)
        return;
    ui->mdiArea->setActiveSubWindow(qobject_cast<QMdiSubWindow *>(window));
}

MdiForm *MainView::createMdiChild(ControllerInterface *cont,ArincModelInterface *ami)
{
    MdiForm *child = new MdiForm(cont,ami);

    ui->mdiArea->addSubWindow(child);
    child->showMaximized();

    return child;
}


