#include "modelconfparams.h"

ModelConfParams::ModelConfParams(int rows, int columns,QObject *parent):QAbstractTableModel(parent)
{
    this->rows=rows;
    this->columns=columns;
}

void ModelConfParams::insertParam()
{
    ++rows;
    for(int i=0;i<columns;++i){
        QModelIndex index=this->index(rows,i);
        dat[index]="";
    }
    QModelIndex index=this->index(rows,0);
    beginInsertRows(index,rows,rows);
    endInsertRows();
}

void ModelConfParams::delParam(int row)
{

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
    if (!index.isValid()) {
        return QVariant();
    }
    return (role == Qt::DisplayRole || role == Qt::EditRole) ? dat[index] : QVariant();
}

bool ModelConfParams::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole){
        dat[index]=value;
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

QVariant ModelConfParams::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole){
        return QVariant();
    }
    return (orientation == Qt::Horizontal) ? QString("Number") : QString::number(section+1);
}

Qt::ItemFlags ModelConfParams::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);
    return index.isValid() ? (flags | Qt::ItemIsEditable) : flags;
}
