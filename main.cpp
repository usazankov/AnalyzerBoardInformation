#include <QApplication>
#include "FormsModels/mainview.h"
#include "maincontroller.h"
#include <QTextStream>
#include <QPalette>

static void setStyle();
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    setStyle();
    try {
        MainView w;
        MainController c(&w);
        w.show();
        return a.exec();
        } catch (const std::bad_alloc& e) {
            std::cout << "Allocation failed: " << e.what() << '\n';
        }


}
static void setStyle()
{
    //QApplication::setStyle(QStyleFactory::create("Fusion"));
    QFile f(":qdarkstyle/style.qss");
    if (!f.exists())
    {
        printf("Unable to set stylesheet, file not found\n");
    }
    else
    {
        f.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&f);
        qApp->setStyleSheet(ts.readAll());
    }
}


