#include "qlabelhasword.h"

QLabelHasWord::QLabelHasWord(QWidget *parent, int adress):QLabel(parent)
{
    this->adress=adress;
    if (adress==0)
        this->setText("- Слово отсутствует");
}

void QLabelHasWord::setAdress(int adress)
{
    this->adress=adress;
}

void QLabelHasWord::update(const QMap<int, ArincParametr *> &map)
{
    if(map.contains(adress)){
        if(map[adress]->HasValue()&&adress!=0)
            this->setText("");
        else
            this->setText("- Слово отсутствует");
    }else
        this->setText("- Слово отсутствует");
}
