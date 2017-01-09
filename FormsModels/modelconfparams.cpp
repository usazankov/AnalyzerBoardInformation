#include "modelconfparams.h"

ModelConfParams::ModelConfParams(int rows, int columns,QObject *parent):QAbstractTableModel(parent)
{
    this->rows=rows;
    this->columns=columns;
    if(rows!=0){
        dat.append(new ConfParametr());
    }
}

void ModelConfParams::insertParam()
{

    dat.append(new ConfDecParametr());
    ++rows;
    QModelIndex index=this->index(rows,0);
    beginInsertRows(index,rows,rows);
    endInsertRows();
}

void ModelConfParams::delParam(int row)
{
    if(row>=0){
        delete dat.at(row);
        dat.removeAt(row);
        --rows;
        beginResetModel();
        endResetModel();
    }
}

ConfParametr *ModelConfParams::parametr_to_change(int row)
{
    return dat.at(row);
}

const ConfParametr *ModelConfParams::parametr(int row) const
{
    return dat.at(row);
}

params::TypeParametr ModelConfParams::typeParametr(int row)const
{
    return dat.at(row)->type;
}

QList<ConfParametr *> ModelConfParams::getConfParametrs() const
{
    return dat;
}

QList<ConfParametr *> *ModelConfParams::getConfParametrsPtr()
{
    return &dat;
}

void ModelConfParams::setConfParametrs(const QList<ConfParametr *> &list)
{
    /*foreach (ConfParametr* p, list) {
        cout<<"name="<<p->name.toStdString()<<endl;

    }*/
    clearModel();
    foreach (ConfParametr* p, list) {
        dat.push_back(p);
    }
    rows=list.count();
    columns=4;
    beginResetModel();
    endResetModel();
}

void ModelConfParams::clearModel()
{
    foreach (ConfParametr* p, dat) {
        delete p;
    }
    dat.clear();
    rows=0;
    columns=0;
    beginResetModel();
    endResetModel();
}

int ModelConfParams::rowCount(const QModelIndex &parent) const
{
    return rows;
}

int ModelConfParams::columnCount(const QModelIndex &parent) const
{
    return columns;
}

QVariant ModelConfParams::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()){
        return QVariant();
    }
    if(role == Qt::DisplayRole || role == Qt::EditRole){
        switch(index.column()){
        case 0:
            return dat.at(index.row())->name;
            break;
        case 1:
            return dat.at(index.row())->dimension;
            break;
        case 2:
            return dat.at(index.row())->adress;
            break;
        case 3:
            switch(dat.at(index.row())->type){
            case params::DEC:
                return "Десятичный";
                break;
            case params::DISCR:
                return "Дискретный";
                break;
            case params::DISCR_DEC:
                return "Дискретно-десятичный";
                break;
            case params::DD:
                return "Двоично-десятичный";
                break;
            default:
                return QVariant();
                break;
            }
            break;
        }
    }else return QVariant();
}

bool ModelConfParams::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole){
        ConfParametr *conf=dat.at(index.row());
        ConfParametr *param_new;
        params::TypeParametr temp=conf->type;
        switch(index.column()){
        case 0:
            conf->name=value.toString();
            break;
        case 1:
            conf->dimension=value.toString();

            break;
        case 2:
            conf->adress=value.toInt();

            break;
        case 3:
            switch(value.toInt()){
            case 0:conf->type=params::DEC;
                if(temp!=conf->type){
                    param_new=new ConfDecParametr(*conf);
                    delete dat.at(index.row());
                    dat.replace(index.row(),param_new);
                }
                break;
            case 1:conf->type=params::DISCR;
                if(temp!=conf->type){
                    param_new=new ConfDiscrParametr(*conf);
                    delete dat.at(index.row());
                    dat.replace(index.row(),param_new);
                }
                break;
            case 2:conf->type=params::DISCR_DEC;
                if(temp!=conf->type){

                }
                break;
            case 3:conf->type=params::DD;
                if(temp!=conf->type){

                }
                break;
            default:
                break;
            }

            break;
        default:
            break;
        }
        emit dataChanged(index, index);
        emit changeContent();
        return true;
    }
    return false;
}

QVariant ModelConfParams::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole){
        return QVariant();
    }
    if(orientation == Qt::Horizontal){
        switch (section) {
        case 0:
            return QString("Имя");
            break;
        case 1:
            return QString("Размерность");
            break;
        case 2:
            return QString("Адрес");
            break;
        case 3:
            return QString("Тип");
            break;
        default:
            break;
        }
    }else if(orientation = Qt::Vertical){
        return QString::number(section+1);
    }
    return QVariant();
}

Qt::ItemFlags ModelConfParams::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);
    return index.isValid() ? (flags | Qt::ItemIsEditable) : flags;
}


ModelConfDiscrParams::ModelConfDiscrParams(int rows, int columns, QObject *parent):QAbstractTableModel(parent)
{
    this->rows=rows;
    this->columns=columns;
}

ModelConfDiscrParams::ModelConfDiscrParams(const ModelConfDiscrParams &m, QObject *parent):QAbstractTableModel(parent)
{
    rows=m.rows;
    columns=m.columns;
    states=m.states;
}

void ModelConfDiscrParams::insertParam()
{
    states.insertState(new State());
    ++rows;
    QModelIndex index=this->index(rows,0);
    beginInsertRows(index,rows,rows);
    endInsertRows();
}

void ModelConfDiscrParams::delParam(int row)
{
    if(row>=0){
        states.deleteState(row);
        --rows;
        beginResetModel();
        endResetModel();
    }
}

StateContanier *ModelConfDiscrParams::getStates()
{
    return &states;
}

ModelConfDiscrParams &ModelConfDiscrParams::operator =(const ModelConfDiscrParams &conf)
{
    rows=conf.rows;
    columns=conf.columns;
    states=conf.states;
    return *this;
}

int ModelConfDiscrParams::rowCount(const QModelIndex &) const
{
    return rows;
}

int ModelConfDiscrParams::columnCount(const QModelIndex &) const
{
    return columns;
}

QVariant ModelConfDiscrParams::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()){
        return QVariant();
    }
    if(role == Qt::DisplayRole || role == Qt::EditRole){
        switch (index.column()) {
        case 0:
            return states.getState(index.row())->getNameState();
            break;
        case 1:
            return states.getState(index.row())->getDigit();
            break;
        case 2:
            return states.getState(index.row())->getState1();
            break;
        case 3:
            return states.getState(index.row())->getState0();
            break;
        default:
            return QVariant();
            break;
        }
    }else return QVariant();
}

bool ModelConfDiscrParams::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole){
        switch (index.column()) {
        case 0:
            states.setNameState(value.toString(),index.row());
            break;
        case 1:
            states.setDigit(value.toInt(),index.row());
            break;
        case 2:
            states.setState1(value.toString(),index.row());
            break;
        case 3:
            states.setState0(value.toString(),index.row());
            break;
        default:
            break;
        }
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

QVariant ModelConfDiscrParams::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole){
        return QVariant();
    }
    if(orientation == Qt::Horizontal){
        switch (section) {
        case 0:
            return QString("Имя команды");
            break;
        case 1:
            return QString("Бит");
            break;
        case 2:
            return QString("При 1");
            break;
        case 3:
            return QString("При 0");
            break;
        default:
            break;
        }
    }else if(orientation = Qt::Vertical){
        return QString::number(section+1);
    }
    return QVariant();
}

Qt::ItemFlags ModelConfDiscrParams::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);
    return index.isValid() ? (flags | Qt::ItemIsEditable) : flags;
}

params::TypeParametr ConfParametr::getType() const
{
        if (typeid(*this)==typeid(ConfDecParametr))
            return params::DEC;
        else if(typeid(*this)==typeid(ConfDiscrParametr))
            return params::DISCR;
        else{
            cout<<"\nНеправильный тип";
            return params::DEC;
        }
}

params::TypeParametr ConfParametr::toTypeParametr(int i)
{
    params::TypeParametr t;
    switch (i) {
    case 0:
        t=params::DEC;
        break;
    case 1:
        t=params::DISCR;
        break;
    case 2:
        t=params::DISCR_DEC;
        break;
    case 3:
        t=params::DD;
        break;
    default:
        t=params::DEC;
        break;
    }
    return t;
}
