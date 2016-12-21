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
    QPalette palette;
    palette.setColor(QPalette::Light, QColor(70,70,70));
    ui->mdiArea->setPalette(palette);
    createActions();
    createToolBars();
    createMenu();
    ui->mdiArea->closeActiveSubWindow();
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
    fileToolBar->setIconSize(QSize(24,24));

    deviceToolBar=this->addToolBar(tr("Device"));
    deviceToolBar->addAction(action_add_device);
    deviceToolBar->addAction(action_del_device);
    deviceToolBar->addAction(action_confparams_device);
    deviceToolBar->setIconSize(QSize(24,24));

    startingToolBar=this->addToolBar(tr("Starting"));
    startingToolBar->addAction(action_start);
    startingToolBar->addAction(action_stop);
    startingToolBar->setIconSize(QSize(24,24));
}

void MainView::createActions()
{
    action_start = new QAction(this);
    action_start->setObjectName("action_start");
    QIcon icon6;
    icon6.addFile(QStringLiteral(":/images/ok.png"), QSize(), QIcon::Normal, QIcon::Off);
    action_start->setIcon(icon6);
    action_start->setText("&Запуск");
    action_start->setIconVisibleInMenu(false);

    action_stop = new QAction(this);
    action_stop->setObjectName("action_stop");
    QIcon icon7;
    icon7.addFile(QStringLiteral(":/images/cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
    action_stop->setIcon(icon7);
    action_stop->setText("&Стоп");
    action_stop->setIconVisibleInMenu(false);

    action_add_device = new QAction(this);
    action_add_device->setObjectName(QStringLiteral("action_add_device"));
    QIcon icon;
    icon.addFile(QStringLiteral(":/images/add.png"), QSize(), QIcon::Normal, QIcon::Off);
    action_add_device->setIcon(icon);
    action_add_device->setText("&Добавить устройство");
    action_add_device->setIconVisibleInMenu(false);
    action_del_device = new QAction(this);
    action_del_device->setObjectName(QStringLiteral("action_add_device"));
    QIcon icon1;
    icon1.addFile(QStringLiteral(":/images/del.png"), QSize(), QIcon::Normal, QIcon::Off);
    action_del_device->setIcon(icon1);
    action_del_device->setText("&Удалить устройство");
    action_del_device->setIconVisibleInMenu(false);
    action_confparams_device = new QAction(this);
    action_confparams_device->setObjectName(QStringLiteral("action_confparams_device"));
    QIcon icon5;
    icon5.addFile(QStringLiteral(":/images/settings.png"), QSize(), QIcon::Normal, QIcon::Off);
    action_confparams_device->setIcon(icon5);
    action_confparams_device->setText("&Параметры распаковки");
    action_confparams_device->setIconVisibleInMenu(false);
    action_open_file = new QAction(this);
    action_open_file->setObjectName(QStringLiteral("action_open_file"));
    QIcon icon2;
    icon2.addFile(QStringLiteral(":/images/open.png"), QSize(),QIcon::Normal, QIcon::Off);
    action_open_file->setIcon(icon2);
    action_open_file->setText("&Открыть");
    action_open_file->setIconVisibleInMenu(false);
    action_save_file = new QAction(this);
    action_save_file->setObjectName(QStringLiteral("action_save_file"));
    QIcon icon3;
    icon3.addFile(QStringLiteral(":/images/save.png"), QSize(),QIcon::Normal, QIcon::Off);
    action_save_file->setIcon(icon3);
    action_save_file->setText("&Сохранить");
    action_save_file->setIconVisibleInMenu(false);
    action_exit = new QAction(this);
    action_exit->setObjectName(QStringLiteral("action_exit"));
    QIcon icon4;
    icon4.addFile(QStringLiteral(":/images/cancel.png"), QSize(),QIcon::Normal, QIcon::Off);
    action_exit->setIcon(icon4);
    action_exit->setText("&Выход");
    action_exit->setIconVisibleInMenu(false);
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

void MainView::closeActiveMdiForm()
{
    ui->mdiArea->closeActiveSubWindow();
}



void MainView::createMenu()
{
    menuBar = new QMenuBar(this);
    menuBar->setObjectName(QStringLiteral("menuBar"));
    menuBar->setGeometry(QRect(0, 0, 760, 19));

    QPalette palette;
    palette.setColor(QPalette::Window, QColor(53,53,53));
    palette.setColor(QPalette::Base, QColor(53,53,53));
    menuBar->setPalette(palette);
    menuFile = new QMenu(menuBar);
    menuFile->setObjectName(QStringLiteral("menuFile"));
    menuFile->setTitle("&Файл");
    menuFile->setPalette(palette);

    menuDevice = new QMenu(menuBar);
    menuDevice->setObjectName(QStringLiteral("menuDevice"));
    menuDevice->setTitle("&Устройство");
    menuDevice->setPalette(palette);
    this->setMenuBar(menuBar);
    menuBar->addAction(menuFile->menuAction());
    menuBar->addAction(menuDevice->menuAction());
    menuFile->addAction(action_open_file);
    menuFile->addAction(action_save_file);
    menuFile->addSeparator();
    menuFile->addAction(action_exit);
    menuDevice->addAction(action_add_device);
    menuDevice->addAction(action_del_device);
    menuDevice->addAction(action_confparams_device);
    menuDevice->addSeparator();
    menuDevice->addAction(action_start);
    menuDevice->addAction(action_stop);
}


void MainView::setActiveSubWindow(QWidget *window)
{
    if (!window)
        return;
    ui->mdiArea->setActiveSubWindow(qobject_cast<QMdiSubWindow *>(window));
}


MdiForm *MainView::createMdiChild(QString nameTitle,int index)
{
    MdiForm *child = new MdiForm(nameTitle,index);
    ui->mdiArea->addSubWindow(child);
    child->showMaximized();

    return child;
}


