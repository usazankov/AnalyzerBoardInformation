#include <QApplication>
#include <QStyleFactory>
#include "mainview.h"
#include "maincontroller.h"


void setPalette();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    setPalette();
    MainView w;
    MainController c(&w);
    w.show();
    return a.exec();
}

void setPalette(){
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    QPalette palette;
    palette.setColor(QPalette::Window, QColor(53,53,53));
    palette.setColor(QPalette::WindowText, QColor(200,200,200));
    palette.setColor(QPalette::Base, QColor(35,35,35));
    palette.setColor(QPalette::AlternateBase, QColor(53,53,53));
    palette.setColor(QPalette::ToolTipBase, Qt::white);
    palette.setColor(QPalette::ToolTipText, Qt::black);
    palette.setColor(QPalette::Text, QColor(200,200,200));
    palette.setColor(QPalette::Button, QColor(53,53,53));
    palette.setColor(QPalette::ButtonText, QColor(200,200,200));
    palette.setColor(QPalette::BrightText, Qt::red);
    palette.setColor(QPalette::Light,Qt::red);
    //142,45,197
    palette.setColor(QPalette::Highlight, QColor(140,140,140).lighter());
    palette.setColor(QPalette::HighlightedText, Qt::black);
    qApp->setPalette(palette);
}
