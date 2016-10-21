#include "mainview.h"
#include <QApplication>
#include "maincontroller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainView w;
    w.show();
    MainController controller(&w);
    return a.exec();
}
