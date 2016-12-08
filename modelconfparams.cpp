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

TypeParametr ModelConfParams::typeParametr(int row)const
{
    return dat.at(row)->type;
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
            case DEC:
                return "Десятичный";
                break;
            case DISCR:
                return "Дискретный";
                break;
            case DISCR_DEC:
                return "Дискретно-десятичный";
                break;
            case DD:
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
        TypeParametr temp=conf->type;
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
            case 0:conf->type=DEC;
                if(temp!=conf->type){
                    param_new=new ConfDecParametr(*conf);
                    delete dat.at(index.row());
                    dat.replace(index.row(),param_new);
                }
                break;
            case 1:conf->type=DISCR;
                if(temp!=conf->type){
                    param_new=new ConfDiscrParametr(*conf);
                    delete dat.at(index.row());
                    dat.replace(index.row(),param_new);
                }
                break;
            case 2:conf->type=DISCR_DEC;
                if(temp!=conf->type){

                }
                break;
            case 3:conf->type=DD;
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
            states.getState(index.row())->setNameState(value.toString());
            break;
        case 1:
            states.getState(index.row())->setDigit(value.toInt());
            break;
        case 2:
            states.getState(index.row())->setState1(value.toString());
            break;
        case 3:
            states.getState(index.row())->setState0(value.toString());
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
