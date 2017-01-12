#ifndef MDIFORMDISCR_H
#define MDIFORMDISCR_H

#include <QWidget>
#include <QAbstractItemModel>
#include <QLabel>
#include "arincparametrobserver.h"
#include "qlabelhasword.h"
namespace Ui {
class MdiFormDiscr;
const QString TABLE_STATE="Значение";
}



class ModelDiscrTable: public QAbstractTableModel, public ArincParametrObserver
{
    Q_OBJECT
private:
    int rows;
    int columns;
    int adress;
    QHash<QModelIndex, QVariant> dat;
    QHash<int, QString> names_header;
    QMap<int, ArincParametr*>::const_iterator iter;
    QStringList names_states;
    QStringList value_states;
    void setRowCount(int row);
    void setColumnCount(int column);
    int countOfStates;
public:
    explicit ModelDiscrTable(int adress, int row=0,int column=0, QObject *parent = 0);
    explicit ModelDiscrTable(const ModelDiscrTable &table, QObject *parent=0);
    int rowCount(const QModelIndex &) const;
    int columnCount(const QModelIndex &) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    void setAdress(int adress);
    int getAdress()const;
    ~ModelDiscrTable();
    // ArincParametrObserver interface
public:
    void update(const QMap<int, ArincParametr *> &map);

    // ArincParametrObserver interface
public:
    int timeToUpdate();
};

class MdiFormDiscr : public QWidget
{
    Q_OBJECT
public:
    explicit MdiFormDiscr(QWidget *parent = 0);
    void setModel(ModelDiscrTable *model, const QString &name);
    int adress()const;
    QLabelHasWord* LabelHasWord();
    ~MdiFormDiscr();

private:
    Ui::MdiFormDiscr *ui;
    QString name;
    int adr;
};

#endif // MDIFORMDISCR_H
