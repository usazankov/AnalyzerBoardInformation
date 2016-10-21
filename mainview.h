#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QMainWindow>
#include <QToolBar>
#include <QIcon>
#include "mdiform.h"
#include <QMdiSubWindow>
namespace Ui {
class MainView;
}

class MainView : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainView(QWidget *parent = 0);

    ~MainView();
private:
    QToolBar *fileToolBar;
    QToolBar *deviceToolBar;
    void createToolBars();
    Ui::MainView *ui;
    MdiForm *activeMdiChild();
    QMdiSubWindow *findMdiChild(const QString &fileName);
    void setStyle();
private slots:
    void setActiveSubWindow(QWidget *window);
public slots:
    MdiForm* createMdiChild(ControllerInterface *cont, ArincModelInterface *ami);
};

#endif // MAINVIEW_H
