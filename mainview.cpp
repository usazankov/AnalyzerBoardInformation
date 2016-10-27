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
    createActions();
    createToolBars();
    createMenu();
}

void MainView::connectActionsToSlots()
{

}

MainView::~MainView()
{
    delete ui;
}

void MainView::createToolBars()
{
    fileToolBar=this->addToolBar(tr("File"));
    fileToolBar->addAction(action_open_file);
    fileToolBar->addAction(action_save_file);

    deviceToolBar=this->addToolBar(tr("Device"));
    deviceToolBar->addAction(action_add_device);
    deviceToolBar->addAction(action_del_device);
}

void MainView::createActions()
{
    action_add_device = new QAction(this);
    action_add_device->setObjectName(QStringLiteral("action_add_device"));
    QIcon icon;
    icon.addFile(QStringLiteral(":/images/cut.png"), QSize(), QIcon::Normal, QIcon::Off);
    action_add_device->setIcon(icon);
    action_add_device->setText("&Добавить устройство");

    action_del_device = new QAction(this);
    action_del_device->setObjectName(QStringLiteral("action_add_device"));
    QIcon icon1;
    icon1.addFile(QStringLiteral(":/images/paste.png"), QSize(), QIcon::Normal, QIcon::Off);
    action_del_device->setIcon(icon1);
    action_del_device->setText("&Удалить устройство");

    action_open_file = new QAction(this);
    action_open_file->setObjectName(QStringLiteral("action_open_file"));
    QIcon icon2;
    icon2.addFile(QStringLiteral(":/images/open.png"), QSize(),QIcon::Normal, QIcon::Off);
    action_open_file->setIcon(icon2);
    action_open_file->setText("&Открыть");

    action_save_file = new QAction(this);
    action_save_file->setObjectName(QStringLiteral("action_save_file"));
    QIcon icon3;
    icon3.addFile(QStringLiteral(":/images/save.png"), QSize(),QIcon::Normal, QIcon::Off);
    action_save_file->setIcon(icon3);
    action_save_file->setText("&Сохранить");

    action_exit = new QAction(this);
    action_exit->setObjectName(QStringLiteral("action_exit"));
    QIcon icon4;
    icon4.addFile(QStringLiteral(":/images/cut.png"), QSize(),QIcon::Normal, QIcon::Off);
    action_exit->setIcon(icon4);
    action_exit->setText("&Выход");
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

void MainView::createMenu()
{
    menuBar = new QMenuBar(this);
    menuBar->setObjectName(QStringLiteral("menuBar"));
    menuBar->setGeometry(QRect(0, 0, 760, 19));
    menuFile = new QMenu(menuBar);
    menuFile->setObjectName(QStringLiteral("menuFile"));
    menuFile->setTitle("&Файл");
    menuDevice = new QMenu(menuBar);
    menuDevice->setObjectName(QStringLiteral("menuDevice"));
    menuDevice->setTitle("&Устройство");
    this->setMenuBar(menuBar);
    menuBar->addAction(menuFile->menuAction());
    menuBar->addAction(menuDevice->menuAction());
    menuFile->addAction(action_open_file);
    menuFile->addAction(action_save_file);
    menuFile->addSeparator();
    menuFile->addAction(action_exit);
    menuDevice->addAction(action_add_device);
    menuDevice->addAction(action_del_device);
}


void MainView::setActiveSubWindow(QWidget *window)
{
    if (!window)
        return;
    ui->mdiArea->setActiveSubWindow(qobject_cast<QMdiSubWindow *>(window));
}


MdiForm *MainView::createMdiChild(ControllerInterface *cont, ArincModelInterface *ami)
{
    MdiForm *child = new MdiForm(cont,ami);

    ui->mdiArea->addSubWindow(child);
    child->showMaximized();

    return child;
}


