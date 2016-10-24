#ifndef ARINCPARAMETR_H
#define ARINCPARAMETR_H
#include "parametr.h"
#include "dataarinc32.h"
#include "states.h"
#include <iostream>
namespace params {
class ArincParametr;
class ArincDecParametr;
}
class ArincParametr : public Parametr
{
public:
    explicit ArincParametr(int word=0);
    explicit ArincParametr(int word,QString Name, QString Dimension="");
    virtual void setWord(int word);
    virtual int Adress()const;
    virtual int MatrixState()const;
    virtual int UnpackWord()const;
    virtual TypeParametr Type() const;
    virtual QStringList FormatAllValues()const;
    virtual QString FormatValue(Format f)const;
    virtual ~ArincParametr();
    static int count;
};


using namespace std;
class ArincDecParametr : public ArincParametr
{
public:
    explicit ArincDecParametr(int word=0, double UnpackConst=params::DEFAULT_UNPACK_CONST);
    explicit ArincDecParametr(int word, QString name, QString Dimension, double UnpackConst=params::DEFAULT_UNPACK_CONST);
    double Value()const;
    void setUnpackConst(double unpack_const);
    double getUnpackConst()const;
    QStringList FormatAllValues()const;
    QString FormatValue(Format f)const;
    TypeParametr Type()const;
    ~ArincDecParametr();
private:
    double unpack_const;
};

namespace params {
class ArincDiscrParametr;
}
class ArincDiscrParametr: public ArincParametr
{
public:
    explicit ArincDiscrParametr(int word=0);
    explicit ArincDiscrParametr(int word, QString Name);
    explicit ArincDiscrParametr(int word, StateContanier *sc);
    explicit ArincDiscrParametr(int word, QString Name, StateContanier *sc);
    QString displayStates()const;
    QStringList getStates()const;
    void setStates(StateContanier *sc);
    QStringList FormatAllValues()const;
    QString FormatValue(Format f)const;
    QStringList getNameStates()const;
    QStringList getValueStates()const;
    TypeParametr Type()const;
    static int k;
private:
    StateContanier *states;
    bool hasStates()const;
};

class ArincDecDiscrParametr:public ArincParametr
{

public:
    explicit ArincDecDiscrParametr(int word);
    explicit ArincDecDiscrParametr(int word,QString name);
};

#endif // ARINCPARAMETR_H
