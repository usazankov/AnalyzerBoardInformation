#ifndef MODELCONFPARAMS_H
#define MODELCONFPARAMS_H

#include <QObject>
#include <QAbstractTableModel>
#include <iostream>
#include "UnpackingArinc/states.h"
#include <QDataStream>
#include <typeinfo>
namespace params {
    enum TypeParametr{DEC,DISCR,DISCR_DEC,DD};
}

struct ConfParametr{
    QString name;
    QString dimension;
    int adress;
    params::TypeParametr type;
    ConfParametr(){
        type=params::DEC;
        name="-";
        dimension="-";
        adress=0;
    }
    ConfParametr(const ConfParametr& conf){
        type=conf.type;
        name=conf.name;
        dimension=conf.dimension;
        adress=conf.adress;
    }
    virtual params::TypeParametr getType()const;
    static params::TypeParametr toTypeParametr(int i);

    friend QDataStream& operator >>(QDataStream& st, ConfParametr &conf){
        int type;
        st>>type;
        conf.type=ConfParametr::toTypeParametr(type);
        st>>conf.name;
        st>>conf.dimension;
        st>>conf.adress;
        return st;
    }
    friend QDataStream& operator <<(QDataStream& st,ConfParametr conf){
        st<<conf.type;
        st<<conf.name;
        st<<conf.dimension;
        st<<conf.adress;
        return st;
    }
    virtual ~ConfParametr(){}
};


struct ConfDecParametr:public ConfParametr{
    double unpack;
    int least_bit;
    int most_bit;
    ConfDecParametr():ConfParametr(){
        type=params::DEC;
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
    friend QDataStream& operator >>(QDataStream& st, ConfDecParametr &conf){
        int type;
        st>>type;
        conf.type=conf.toTypeParametr(type);
        st>>conf.name;
        st>>conf.dimension;
        st>>conf.adress;
        st>>conf.least_bit;
        st>>conf.most_bit;
        st>>conf.unpack;
        return st;
    }
    friend QDataStream& operator <<(QDataStream& st,ConfDecParametr conf){
        st<<conf.type;
        st<<conf.name;
        st<<conf.dimension;
        st<<conf.adress;
        st<<conf.least_bit;
        st<<conf.most_bit;
        st<<conf.unpack;
        return st;
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
    ModelConfDiscrParams(const ModelConfDiscrParams& m,QObject *parent=0);
    void insertParam();
    void delParam(int row);
    StateContanier* getStates();
    ModelConfDiscrParams& operator =(const ModelConfDiscrParams&conf);
    friend QDataStream& operator <<(QDataStream& st,ModelConfDiscrParams conf){
        st<<conf.rows;
        st<<conf.columns;
        st<<conf.states;
        return st;
    }
    friend QDataStream& operator >>(QDataStream& st, ModelConfDiscrParams &conf){
        st>>conf.rows;
        st>>conf.columns;
        for(int i=0;i<conf.rows;++i)
            conf.states.insertState(new State());
        st>>conf.states;
        conf.beginResetModel();
        conf.endResetModel();
        return st;
    }
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
    ConfDiscrParametr():ConfParametr(){
        type=params::DISCR;
    }
    ConfDiscrParametr(const ConfDiscrParametr& conf):ConfParametr(conf){
        model=conf.model;
    }
    ConfDiscrParametr(const ConfParametr& conf):ConfParametr(conf){
    }
    friend QDataStream& operator >>(QDataStream& st, ConfDiscrParametr &conf){
        int type;
        st>>type;
        conf.type=conf.toTypeParametr(type);
        st>>conf.name;
        st>>conf.dimension;
        st>>conf.adress;
        st>>conf.model;
        return st;
    }
    friend QDataStream& operator <<(QDataStream& st,ConfDiscrParametr conf){
        st<<conf.type;
        st<<conf.name;
        st<<conf.dimension;
        st<<conf.adress;
        st<<conf.model;
        return st;
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
    params::TypeParametr typeParametr(int row) const;
    QList<ConfParametr*> getConfParametrs()const;
    QList<ConfParametr*>* getConfParametrsPtr();
    void setConfParametrs(const QList<ConfParametr*> &list);
private:
    void clearModel();
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
