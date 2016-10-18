#include "mainview.h"
#include "ui_mainview.h"

MainView::MainView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainView)
{
    ui->setupUi(this);
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

void MainView::modifyActions()
{

}
