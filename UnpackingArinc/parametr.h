#ifndef PARAMETR_H
#define PARAMETR_H

#include <QObject>
#include "databehavior.h"
#include <QStringList>
#include <iostream>
namespace params {
const double ARINC_SCALE=1048576;
const double DEFAULT_UNPACK_CONST=0;
class Parametr;
}
using namespace std;
class Parametr
{
private:
    QString name;//Имя параметра
    QString dimension;//Размерность параметра
    bool hasValue;
    bool registered_flag;
public:
    enum TypeParametr{NoType=0,ARINC_DEC=1,ARINC_DISCR=2,ARINC_DEC_DISCR=3,ARINC_PARAM=4};
    enum Format{NoFormat=0,NameParametr=1,DimensionParametr=2,ValueParametr=4,
                     StateParametr=8,MatrixStateParametr=16,Adress=32,UnpackValue=64};
    explicit Parametr();
    explicit Parametr(QString Name, QString Dimension="");
    explicit Parametr(const Parametr &p);
    QString Name()const;
    QString Dimension()const;
    void setUnpackValue(params::Part part,int value);
    void setFormat(int f);
    void setDefaultFormat();
    void setName(QString name);
    void setDimension(QString dim);
    void setDataBehavior(DataBehavior *db);
    void setHasValue(bool flag);
    void setRegistered(bool flag);
    bool HasValue()const;
    bool registered()const;
    DataBehavior* getDataBehavior();
    virtual QStringList FormatAllValues()const;//Форматированный вывод данных
    virtual QString FormatValue(Format f)const;
    virtual TypeParametr Type()const;
    virtual ~Parametr();
protected:
    DataBehavior *db;//Переменная (указатель) определяет состав данных
    int format;// Определяет формат вывода данных (что выдает функция FormatValue())
    bool ContainsBitFormat(Format f)const;
};


#endif // PARAMETR_H
