#ifndef MDIFORM_H
#define MDIFORM_H

#include <QWidget>
#include "controllerinterface.h"
#include "arincmodelinterface.h"
#include <QAbstractTableModel>
#include <QHash>
#include <iostream>
#include <QTableView>
#include <QVBoxLayout>
#include <QLabel>
#include "mdiformdiscr.h"
namespace Ui {
class MdiForm;
class ModelTable;
const int COLUMNS_MAIN_TABLE=6;
const int ROWS_MAIN_TABLE=5;
const QString TABLE_NAME="Имя";
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
    QList<QString> visible_columns;
    QMap<int, ArincParametr*>::const_iterator iter;
    void setRowCount(int row);
    void setColumnCount(int column);
    int ColumnCountOfVisibleHeaders();
    int maxRowCount;
    //QAbstractItemModel interface
public:
    explicit ModelTable(int row=0,int column=6, QObject *parent = 0);
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
signals:
    void changeContent();
public slots:
    void setVisibleHeader(bool visible,Parametr::Format f);
};


class MdiForm : public QWidget
{
    Q_OBJECT

public:
    explicit MdiForm(QWidget *parent = 0);
    explicit MdiForm(QString nameTitle, int index, QWidget *parent = 0);
    void setModel(ArincModelInterface *m);
    void addDiscrTable(int adress);
    void setDiscrTable(int index, int adress);
    bool containsDiscrModel(int adress);
    int countDiscrTables()const;
    int countDiscrModels()const;
    void deleteDiscrTable(int adress);
    void setVisibleDiscrTables(bool visible);
    int index()const;
    ~MdiForm();
private:
    Ui::MdiForm *ui;
    ArincModelInterface *model;
    ModelTable *table;
    QAction* actionVisibleAdress;
    QAction* actionVisibleDimension;
    QAction* actionVisibleValue;
    QAction* actionVisibleUnpack;
    QAction* actionVisibleMS;
    QList<MdiFormDiscr*> forms;
    QMap<int, ModelDiscrTable*> discr_models;
    int i;//Индекс окна
    void createActions();
    void connectActionsToSlots();
public slots:
    void resizeTableToContent();
private slots:
    void on_splitter_splitterMoved(int pos, int index);
    void setVisibleAdress(bool f);
    void setVisibleDimension(bool f);
    void setVisibleValue(bool f);
    void setVisibleMS(bool f);
    void setVisibleUnpack(bool f);
signals:
    void MdiFormDeleted(int index);
};


#endif // MDIFORM_H
