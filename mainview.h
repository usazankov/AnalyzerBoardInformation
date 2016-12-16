#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QMainWindow>
#include <QToolBar>
#include <QIcon>
#include "mdiform.h"
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
    void connectActionsToSlots();
    QAction *action_add_device;
    QAction *action_del_device;
    QAction *action_config_device;
    QAction *action_confparams_device;
    QAction *action_open_file;
    QAction *action_save_file;
    QAction *action_exit;
    ~MainView();
private:
    Ui::MainView *ui;
    QToolBar *fileToolBar;
    QToolBar *deviceToolBar;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuDevice;
    MdiForm *activeMdiChild();
    QMdiSubWindow *findMdiChild(const QString &fileName);
    void setStyle();
    void createMenu();
    void createToolBars();
    void createActions();
private slots:
    void setActiveSubWindow(QWidget *window);
public slots:
    MdiForm* createMdiChild(QString nameTitle, int index);
};

#endif // MAINVIEW_H
