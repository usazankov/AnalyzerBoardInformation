#ifndef MODELCONFPARAMS_H
#define MODELCONFPARAMS_H

#include <QObject>
#include <QAbstractTableModel>
#include <iostream>
#include "states.h"
enum TypeParametr{DEC,DISCR,DISCR_DEC,DD};
struct ConfParametr{
    QString name;
    QString dimension;
    int adress;
    TypeParametr type;
    ConfParametr(){
        name="-";
        dimension="-";
        adress=0;
        type=DEC;
    }
    ConfParametr(const ConfParametr& conf){
        name=conf.name;
        dimension=conf.dimension;
        adress=conf.adress;
        type=conf.type;
    }
    virtual ~ConfParametr(){}
};
struct ConfDecParametr:public ConfParametr{
    double unpack;
    int least_bit;
    int most_bit;
    ConfDecParametr(){
        unpack=90.0;
        least_bit=9;
        most_bit=29;
    }
    ConfDecParametr(const ConfDecParametr& conf):ConfParametr(conf){
        unpack=conf.unpack;
        least_bit=conf.least_bit;
        most_bit=conf.most_bit;
    }
    ConfDecParametr(const ConfParametr& conf):ConfParametr(conf){
        unpack=90.0;
        least_bit=9;
        most_bit=29;
    }
    ~ConfDecParametr(){}
};

class ModelConfDiscrParams : public QAbstractTableModel
{
    Q_OBJECT
private:
    int rows;
    int columns;
    StateContanier states;
public:
    ModelConfDiscrParams(int rows=0, int columns=4, QObject *parent=0);
    void insertParam();
    void delParam(int row);
    StateContanier* getStates();
    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &) const;
    int columnCount(const QModelIndex &) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
};

struct ConfDiscrParametr:public ConfParametr{
    ModelConfDiscrParams model;
    ConfDiscrParametr(){

    }
    ConfDiscrParametr(const ConfDiscrParametr& conf):ConfParametr(conf){
        //model=conf.model;
    }
    ConfDiscrParametr(const ConfParametr& conf):ConfParametr(conf){

    }
    ~ConfDiscrParametr(){}
};
class ModelConfParams : public QAbstractTableModel
{
    Q_OBJECT
private:
    int rows;
    int columns;
    QList<ConfParametr*> dat;
public:
    ModelConfParams(int rows=0, int columns=4, QObject *parent=0);
    void insertParam();
    void delParam(int row);
    ConfParametr *parametr_to_change(int row);
    const ConfParametr *parametr(int row)const;
    TypeParametr typeParametr(int row) const;
    QList<ConfParametr*> getConfParametrs()const;
    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
signals:
    void changeContent();
};



#endif // MODELCONFPARAMS_H
