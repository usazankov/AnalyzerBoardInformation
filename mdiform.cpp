#include "mdiform.h"
#include "ui_mdiform.h"

MdiForm::MdiForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MdiForm)
{
    ui->setupUi(this);
}

MdiForm::MdiForm(ControllerInterface *c, ArincModelInterface *ami, QWidget *parent):QWidget(parent), ui(new Ui::MdiForm)
{
    ui->setupUi(this);
    controller=c;
    model=ami;
    table=new ModelTable(Ui::ROWS_MAIN_TABLE,Ui::COLUMNS_MAIN_TABLE);
    ui->tableView->setModel(table);
    model->registerObserver(table);
    ui->tableView_2->setModel(table);
    ui->tableView_3->setModel(table);
}

MdiForm::~MdiForm()
{
    delete ui;
}

void ModelTable::setRowCount(int row)
{
    rows=row;
    this->beginResetModel();
    this->endResetModel();
}

void ModelTable::setColumnCount(int column)
{
    columns=column;
    this->beginResetModel();
    this->endResetModel();
}

int ModelTable::ColumnCountOfVisibleHeaders()
{
    int count=1;
    if(visible_adress)++count;
    if(visible_dimension)++count;
    if(visible_ms)++count;
    if(visible_unpack)++count;
    if(visible_value)++count;
    return count;
}

ModelTable::ModelTable(int row, int column, QObject *parent):QAbstractTableModel(parent)
{
    rows=row;
    columns=column;
    maxRowCount=row;
    visible_adress=1;
    visible_dimension=1;
    visible_value=1;
    visible_unpack=1;
    visible_ms=1;
}

ModelTable::ModelTable(const ModelTable &table, QObject *parent):QAbstractTableModel(parent)
{
    rows=table.rows;
    columns=table.columns;
    maxRowCount=table.rows;
    visible_adress=table.visible_adress;
    visible_dimension=table.visible_dimension;
    visible_value=table.visible_value;
    visible_unpack=table.visible_unpack;
    visible_ms=table.visible_ms;
}

int ModelTable::rowCount(const QModelIndex &) const
{
    return rows;
}

int ModelTable::columnCount(const QModelIndex &) const
{
    return columns;
}

QVariant ModelTable::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()){
        return QVariant();
    }

    if(role == Qt::DisplayRole || role == Qt::EditRole){
        return dat[index];
    }else return QVariant();
}

QVariant ModelTable::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole){
        return QVariant();
    }
    if(orientation==Qt::Vertical){
            return names_header[section];

    }
    if(orientation==Qt::Horizontal){
        if(section==Ui::VALUE)return Ui::TABLE_VALUE;
        else if(section==Ui::MS)return Ui::TABLE_MS;
        else if(section==Ui::ADRESS)return Ui::TABLE_ADRESS;
        else if(section==Ui::DIMENSION)return Ui::TABLE_DIMENSION;
        else if(section==Ui::UNPACK)return Ui::TABLE_UNPACK;
    }
    return QVariant();
}

Qt::ItemFlags ModelTable::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);
    return index.isValid() ? (flags | Qt::ItemIsEditable) : flags;
}

bool ModelTable::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::DisplayRole){
        //emit dataChanged(index, index);
        return true;
    }
    return false;
}

ModelTable::~ModelTable()
{

}

void ModelTable::update(const QMap<int, ArincParametr *> &map)
{
    if(rows!=map.count()){
        setRowCount(map.count());
    }
    int count=0;
    foreach (int adress, map.keys()) {
        //Имя параметра
        names_header[count]=map.value(adress)->FormatValue(Parametr::NameParametr);
        //Значение параметра
        if(visible_value){
            QModelIndex index=this->index(count,Ui::TABLE::VALUE);
            dat[index]=map.value(adress)->FormatValue(Parametr::Format::ValueParametr);
        }
        //Адресс параметра
        if(visible_adress){
            QModelIndex index=this->index(count,Ui::TABLE::ADRESS);
            dat[index]=map.value(adress)->FormatValue(Parametr::Format::Adress);
        }
        //Матрица состояния
        if(visible_ms){
            QModelIndex index=this->index(count,Ui::TABLE::MS);
            dat[index]=map.value(adress)->FormatValue(Parametr::Format::MatrixStateParametr);
        }
        //Размерность
        if(visible_dimension){
            QModelIndex index=this->index(count,Ui::TABLE::DIMENSION);
            dat[index]=map.value(adress)->FormatValue(Parametr::Format::DimensionParametr);
        }
        //Размерность
        if(visible_unpack){
            QModelIndex index=this->index(count,Ui::TABLE::UNPACK);
            dat[index]=map.value(adress)->FormatValue(Parametr::Format::UnpackValue);
        }
        ++count;
    }
}

void ModelTable::setVisibleHeader(bool visible, Parametr::Format f)
{
    int count=ColumnCountOfVisibleHeaders();
    switch(f){
    case Parametr::Format::DimensionParametr:
        visible_dimension=visible;
        break;
    case Parametr::Format::Adress:
        visible_adress=visible;
        break;
    case Parametr::Format::UnpackValue:
        visible_unpack=visible;
        break;
    case Parametr::Format::MatrixStateParametr:
        visible_ms=visible;
        break;
    case Parametr::Format::ValueParametr:
        visible_value=visible;
        break;
    default:
        break;
    }
    int count_after=ColumnCountOfVisibleHeaders();
    if(count!=count_after)
        setColumnCount(count_after);
}
