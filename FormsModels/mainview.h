#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QMainWindow>
#include <QToolBar>
#include <QIcon>
#include "mdiform.h"
#include "mdigrafform.h"
#include <QMdiSubWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QStyleFactory>
namespace Ui {
class MainView;
}
class MainView : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainView(QWidget *parent = 0);
    MdiGrafForm* grafForm(int index);
    QMdiSubWindow* currentActiveWindow();
    void closeActiveMdiForm();
    bool containsIndexMdiGraf(int index);
    QAction *action_add_device;
    QAction *action_del_device;
    QAction *action_config_device;
    QAction *action_confparams_device;
    QAction *action_start;
    QAction *action_stop;
    QAction *action_open_file;
    QAction *action_save_file;
    QAction *action_exit;
    ~MainView();
private:
    Ui::MainView *ui;
    QToolBar *fileToolBar;
    QToolBar *deviceToolBar;
    QToolBar *startingToolBar;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuDevice;
    QMap<int,MdiForm*> devForms;
    QMap<int,MdiGrafForm*> grafForms;
    void createMenu();
    void createToolBars();
    void createActions();
signals:
    void deleteMdiGraf(int);
    void MdiGrafCreated(int,int);
    void grafCreated(int,int,int);
private slots:
    void setActiveSubWindow(QWidget *window);
    void deletedMdiGrafChild(int index);
    void deleteMdiForm(int index);
    void arincModelIsDeleted(int indexMdi);
public slots:
    void activeMdiChild(QMdiSubWindow*mdi);
    MdiForm* createMdiChild(QString nameTitle, int index);
    MdiGrafForm* createMdiGrafChild(QString nameTitle, int index, int indexDevice);
    void addGrafikToMdiChild(int indexChild, int adress,int indexDevice);
    void deleteObserversMdiForm(int index);
    void addObserversMdiForm(int index);
};

#endif // MAINVIEW_H
