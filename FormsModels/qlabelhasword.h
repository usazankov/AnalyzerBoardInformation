#ifndef QLABELHASWORD_H
#define QLABELHASWORD_H
#include <QLabel>
#include "arincparametrobserver.h"
#include <QMap>
namespace Ui {
class QLabelHasWord;
}
class QLabelHasWord: public QLabel, public ArincParametrObserver{
public:
    explicit QLabelHasWord(QWidget* parent=0,int adress=0);
    void setAdress(int adress);
    // ArincParametrObserver interface
public:
    void update(const QMap<int, ArincParametr *> &map, double time);
private:
    int adress;

    // ArincParametrObserver interface
public:
    int timeToUpdate();
};
#endif // QLABELHASWORD_H
