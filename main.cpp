#include <QApplication>
#include "mainview.h"
#include "maincontroller.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainView w;
    MainController c(&w);
    w.show();
    return a.exec();
}
