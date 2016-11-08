#ifndef MODELCONFPARAMS_H
#define MODELCONFPARAMS_H

#include <QObject>
#include <QAbstractTableModel>

class ModelConfParams : public QAbstractTableModel
{
    Q_OBJECT
private:
    int rows;
    int columns;
    QHash<QModelIndex, QVariant> dat;
public:
    ModelConfParams(int rows=1, int columns=4, QObject *parent=0);
    void insertParam();
    void delParam(int row);
    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
};

#endif // MODELCONFPARAMS_H
