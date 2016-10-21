#ifndef MDIFORM_H
#define MDIFORM_H

#include <QWidget>
#include "controllerinterface.h"
#include "arincmodelinterface.h"
#include <QAbstractTableModel>
#include <QHash>
#include <iostream>
#include <QTableView>
namespace Ui {
class MdiForm;
class ModelTable;
const int COLUMNS_MAIN_TABLE=5;
const int ROWS_MAIN_TABLE=5;
enum TABLE{VALUE=0,DIMENSION=1,MS=2,ADRESS=3,UNPACK=4};
const QString TABLE_VALUE="Значение";
const QString TABLE_UNPACK="Всё слово";
const QString TABLE_DIMENSION="Ед.изм";
const QString TABLE_MS="МС";
const QString TABLE_ADRESS="Адрес";

}
using namespace std;
class ModelTable: public QAbstractTableModel, public ArincParametrObserver
{
Q_OBJECT
private:
    int rows;
    int columns;
    QHash<QModelIndex, QVariant> dat;
    QHash<int, QString> names_header;
    QMap<int,int> map_rows;
    QMap<int, ArincParametr*>::const_iterator iter;
    void setRowCount(int row);
    void setColumnCount(int column);
    int ColumnCountOfVisibleHeaders();
    int maxRowCount;
    bool visible_value;
    bool visible_dimension;
    bool visible_unpack;
    bool visible_adress;
    bool visible_ms;
    //QAbstractItemModel interface
public:
    explicit ModelTable(int row,int column, QObject *parent = 0);
    explicit ModelTable(const ModelTable &table, QObject *parent=0);
    int rowCount(const QModelIndex &) const;
    int columnCount(const QModelIndex &) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    ~ModelTable();

    // ArincParametrObserver interface
public:
    void update(const QMap<int, ArincParametr *> &map);
public slots:
    void setVisibleHeader(bool visible,Parametr::Format f);
};

class MdiForm : public QWidget
{
    Q_OBJECT

public:
    explicit MdiForm(QWidget *parent = 0);
    explicit MdiForm(ControllerInterface *c, ArincModelInterface *ami, QWidget *parent = 0);
    void setMod();
    ~MdiForm();
private:
    Ui::MdiForm *ui;
    ControllerInterface *controller;
    ArincModelInterface *model;
    ModelTable *table;
};


#endif // MDIFORM_H
