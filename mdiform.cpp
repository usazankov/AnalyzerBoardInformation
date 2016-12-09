#include "mdiform.h"
#include "ui_mdiform.h"

MdiForm::MdiForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MdiForm)
{
    ui->setupUi(this);
}

MdiForm::MdiForm(QString nameTitle,int index, QWidget *parent):QWidget(parent), ui(new Ui::MdiForm)
{
    ui->setupUi(this);
    this->setWindowTitle(nameTitle);
    table=new ModelTable(0,0);
    this->index=index;
    ui->tableView->setModel(table);
    ui->splitter->setStretchFactor(0,100);
    ui->splitter->setStretchFactor(1,53);
    connect(table,SIGNAL(changeContent()),this,SLOT(resizeTableToContent()));
    ui->tableView->horizontalHeader()->setMinimumSectionSize(100);

}

void MdiForm::setModel(ArincModelInterface *m)
{
    model=m;
    model->registerObserver(table);
    addDiscrTable(0307);
    addDiscrTable(0300);
    addDiscrTable(0310);
    addDiscrTable(0311);
}

void MdiForm::addDiscrTable(int adress)
{
    ModelDiscrTable *mod=new ModelDiscrTable(adress);
    discr_models.push_back(mod);
    QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    QTableView *view = new QTableView(ui->scrollAreaWidgetContents_2);
    view->setMinimumWidth(300);
    view->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    view->verticalHeader()->setMinimumSectionSize(18);
    view->verticalHeader()->setDefaultSectionSize(23);
    view->horizontalHeader()->setMinimumSectionSize(300);
    view->horizontalHeader()->setDefaultSectionSize(300);
    view->setObjectName(QStringLiteral("tableView"));
    sizePolicy1.setHeightForWidth(view->sizePolicy().hasHeightForWidth());
    view->setSizePolicy(sizePolicy1);

    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    view->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    view->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    //view->setMinimumWidth(500);
    view->setSizePolicy(sizePolicy1);
    view->setModel(mod);
    discr_tables.push_back(view);
    QVBoxLayout *layout = new QVBoxLayout();
    box_layout.push_back(layout);
    QLabel *label=new QLabel(ui->scrollAreaWidgetContents_2);
    label->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    QString name;
    if(model->getParametr(adress)!=0)
        name=model->getParametr(adress)->Name()+"(0"+QString::number(adress,8)+")";
    else name="Неизвестный параметр (0"+QString::number(adress,8)+")";
    label->setText(name);
    layout->addWidget(label);
    layout->addWidget(view);
    layout->setSpacing(6);
    ui->verticalLayout_2->addLayout(layout);
    model->registerObserver(mod);
}

void MdiForm::deleteDiscrTable(int adress)
{

}

MdiForm::~MdiForm()
{
    emit MdiFormDeleted(index);
    foreach(ModelDiscrTable *tmod,discr_models)
        delete tmod;
    foreach (QTableView *table, discr_tables) {
        delete table;
    }
    foreach (QVBoxLayout *vbox, box_layout) {
        delete vbox;
    }
    delete ui;
}

void MdiForm::resizeTableToContent()
{
    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();
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

    return count;
}

ModelTable::ModelTable(int row, int column, QObject *parent):QAbstractTableModel(parent)
{
    rows=row;
    columns=column;
    maxRowCount=row;
    visible_columns.push_back(Ui::TABLE_NAME);
    visible_columns.push_back(Ui::TABLE_VALUE);
    visible_columns.push_back(Ui::TABLE_DIMENSION);
    visible_columns.push_back(Ui::TABLE_MS);
    visible_columns.push_back(Ui::TABLE_ADRESS);
    visible_columns.push_back(Ui::TABLE_UNPACK);
}

ModelTable::ModelTable(const ModelTable &table, QObject *parent):QAbstractTableModel(parent)
{
    rows=table.rows;
    columns=table.columns;
    maxRowCount=table.rows;
    visible_columns=table.visible_columns;
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
        return visible_columns[section];
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
        setColumnCount(Ui::COLUMNS_MAIN_TABLE);

    }
    int count=0;
    foreach (int adress, map.keys()) {
        names_header[count]=QString::number(count+1);
        //Имя параметра
        if(visible_columns.contains(Ui::TABLE_NAME)){
            QModelIndex index=this->index(count,visible_columns.indexOf(Ui::TABLE_NAME));
            dat[index]=map.value(adress)->FormatValue(Parametr::Format::NameParametr);
        }
        //Значение параметра
        if(visible_columns.contains(Ui::TABLE_VALUE)){
            QModelIndex index=this->index(count,visible_columns.indexOf(Ui::TABLE_VALUE));
            dat[index]=map.value(adress)->FormatValue(Parametr::Format::ValueParametr);
        }
        //Адресс параметра
        if(visible_columns.contains(Ui::TABLE_ADRESS)){
            QModelIndex index=this->index(count,visible_columns.indexOf(Ui::TABLE_ADRESS));
            dat[index]=map.value(adress)->FormatValue(Parametr::Format::Adress);
        }
        //Матрица состояния
        if(visible_columns.contains(Ui::TABLE_MS)){
            QModelIndex index=this->index(count,visible_columns.indexOf(Ui::TABLE_MS));
            dat[index]=map.value(adress)->FormatValue(Parametr::Format::MatrixStateParametr);
        }
        //Размерность
        if(visible_columns.contains(Ui::TABLE_DIMENSION)){
            QModelIndex index=this->index(count,visible_columns.indexOf(Ui::TABLE_DIMENSION));
            dat[index]=map.value(adress)->FormatValue(Parametr::Format::DimensionParametr);
        }
        //Нераспакованное слово
        if(visible_columns.contains(Ui::TABLE_UNPACK)){
            QModelIndex index=this->index(count,visible_columns.indexOf(Ui::TABLE_UNPACK));
            dat[index]=map.value(adress)->FormatValue(Parametr::Format::UnpackValue);
        }
        ++count;
    }
    QModelIndex topleft=this->index(0,0);
    QModelIndex bottomright=this->index(rows,columns);
    emit dataChanged(topleft, bottomright);
    emit headerDataChanged(Qt::Vertical,0,rows);
    emit changeContent();
}

void ModelTable::setVisibleHeader(bool visible, Parametr::Format f)
{
    int count=visible_columns.count();
    switch(f){
    case Parametr::Format::DimensionParametr:
        if(!visible)visible_columns.remove(visible_columns.indexOf(Ui::TABLE_DIMENSION));
        break;
    case Parametr::Format::Adress:
        if(!visible)visible_columns.remove(visible_columns.indexOf(Ui::TABLE_ADRESS));
        break;
    case Parametr::Format::UnpackValue:
        if(!visible)visible_columns.remove(visible_columns.indexOf(Ui::TABLE_UNPACK));
        break;
    case Parametr::Format::MatrixStateParametr:
        if(!visible)visible_columns.remove(visible_columns.indexOf(Ui::TABLE_MS));
        break;
    case Parametr::Format::ValueParametr:
        if(!visible)visible_columns.remove(visible_columns.indexOf(Ui::TABLE_VALUE));
        break;
    default:
        break;
    }
    int count_after=visible_columns.count();
    cout<<"count="<<count<<endl;
    cout<<"count_after="<<count_after<<endl;
    if(count!=count_after)
        setColumnCount(count_after);

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
            emit dataChanged(index, index);
            names_header[i]=names_states.at(i);
            dat[index]=value_states.at(i);
        }
    }
}

void MdiForm::on_splitter_splitterMoved(int pos, int index)
{

}
