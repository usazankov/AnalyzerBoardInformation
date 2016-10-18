#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QMainWindow>
#include <QToolBar>
#include <QIcon>
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

};

#endif // MAINVIEW_H
