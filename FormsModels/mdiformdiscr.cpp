#include "mdiformdiscr.h"
#include "ui_mdiformdiscr.h"

MdiFormDiscr::MdiFormDiscr(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MdiFormDiscr)
{
    ui->setupUi(this);
    ui->tableView->setMinimumWidth(250);
    ui->tableView->verticalHeader()->setMinimumSectionSize(30);
    ui->tableView->verticalHeader()->setDefaultSectionSize(30);
    ui->tableView->horizontalHeader()->setMinimumSectionSize(100);
    ui->tableView->horizontalHeader()->setDefaultSectionSize(150);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tableView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tableView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->tableView->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->tableView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
}

void MdiFormDiscr::setModel(ModelDiscrTable *model,const QString &name)
{
    ui->tableView->setModel(model);
    ui->label->setAdress(model->getAdress());
    adr=model->getAdress();
    ui->label_2->setText(name);
}

int MdiFormDiscr::adress() const
{
    return adr;
}

QLabelHasWord *MdiFormDiscr::LabelHasWord()
{
    return ui->label;
}

MdiFormDiscr::~MdiFormDiscr()
{
    delete ui;
}

ModelDiscrTable::ModelDiscrTable(int adress, int row, int column, QObject *parent):QAbstractTableModel(parent)
{
    this->adress=adress;
    rows=row;
    columns=column;
}

ModelDiscrTable::ModelDiscrTable(const ModelDiscrTable &table, QObject *parent):QAbstractTableModel(parent)
{
    rows=table.rows;
    columns=table.columns;
    dat=table.dat;
    names_header=table.names_header;
    iter=table.iter;
    adress=table.adress;
}

int ModelDiscrTable::rowCount(const QModelIndex &) const
{
    return rows;
}

int ModelDiscrTable::columnCount(const QModelIndex &) const
{
    return columns;
}

void ModelDiscrTable::setRowCount(int row)
{
    rows=row;
    this->beginResetModel();
    this->endResetModel();
}

void ModelDiscrTable::setColumnCount(int column)
{
    columns=column;
    this->beginResetModel();
    this->endResetModel();
}

QVariant ModelDiscrTable::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()){
        return QVariant();
    }

    if(role == Qt::DisplayRole || role == Qt::EditRole){
        return dat[index];
    }else return QVariant();
}

QVariant ModelDiscrTable::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole){
        return QVariant();
    }
    if(orientation==Qt::Vertical){
            return names_header[section];

    }
    if(orientation==Qt::Horizontal){
        if (section==0)
            return Ui::TABLE_STATE;
        else
        return "";
    }
    return QVariant();
}

Qt::ItemFlags ModelDiscrTable::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);
    return index.isValid() ? (flags | Qt::ItemIsEditable) : flags;
}

bool ModelDiscrTable::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::DisplayRole){
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

void ModelDiscrTable::setAdress(int adress)
{
    this->adress=adress;
}

int ModelDiscrTable::getAdress() const
{
    return adress;
}


ModelDiscrTable::~ModelDiscrTable()
{

}

void ModelDiscrTable::update(const QMap<int, ArincParametr *> &map)
{
    ArincDiscrParametr *temp = dynamic_cast<ArincDiscrParametr*>(map[adress]);
    if(temp!=0){
        if(countOfStates!=temp->getNameStates().count()){
            countOfStates=temp->getNameStates().count();
            setRowCount(countOfStates);
            setColumnCount(1);
        }
        names_states=temp->getNameStates();
        value_states=temp->getValueStates();
        for(int i=0;i<names_states.size();++i){
            QModelIndex index=this->index(i,0);
            names_header[i]=names_states.at(i);
            dat[index]=value_states.at(i);
        }
        QModelIndex topleft=this->index(0,0);
        QModelIndex bottomright=this->index(rows,columns);
        emit dataChanged(topleft, bottomright);
    }
}

int ModelDiscrTable::timeToUpdate()
{
    return Ui::default_time_to_update_tables;
}

