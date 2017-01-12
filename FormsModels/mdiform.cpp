#include "mdiform.h"
#include "ui_mdiform.h"
#include <QThread>
MdiForm::MdiForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MdiForm)
{
    ui->setupUi(this);
    model=Q_NULLPTR;
}

MdiForm::MdiForm(QString nameTitle,int index, QWidget *parent):QWidget(parent), ui(new Ui::MdiForm)
{
    ui->setupUi(this);
    this->setWindowTitle(nameTitle);
    table=new ModelTable(1);
    this->i=index;
    ui->tableView->setModel(table);
    setVisibleDiscrTables(false);
    connect(table,SIGNAL(changeContent()),this,SLOT(resizeTableToContent()));
    createActions();
    connectActionsToSlots();
    ui->tableView->horizontalHeader()->setMinimumSectionSize(100);
    ui->tableView->horizontalHeader()->addAction(actionVisibleValue);
    ui->tableView->horizontalHeader()->addAction(actionVisibleDimension);
    ui->tableView->horizontalHeader()->addAction(actionVisibleMS);
    ui->tableView->horizontalHeader()->addAction(actionVisibleAdress);
    ui->tableView->horizontalHeader()->addAction(actionVisibleUnpack);
    ui->tableView->horizontalHeader()->setContextMenuPolicy(Qt::ActionsContextMenu);
    ui->tableView->addAction(actionBuildGraf);

}

void MdiForm::setModel(ArincModelInterface *m)
{
    model=m;
    model->registerObserver(table);
}

void MdiForm::addDiscrTable(int adress)
{
    MdiFormDiscr* discr = new MdiFormDiscr(ui->scrollAreaWidgetContents_2);
    ModelDiscrTable *mod = new ModelDiscrTable(adress);
    QString name;
    if(model->getParametr(adress)!=0){
        name=model->getParametr(adress)->Name()+" (0"+QString::number(adress,8)+")";
    }
    discr->setModel(mod,name);
    discr_models[adress]=mod;
    forms.append(discr);
    ui->verticalLayout_2->insertWidget(ui->verticalLayout_2->count()-1,discr);
    model->registerObserver(mod);
    model->registerObserver(discr->LabelHasWord());
}

void MdiForm::setDiscrTable(int index,int adress)
{
    ModelDiscrTable *mod = new ModelDiscrTable(adress);
    QString name;
    if(model->getParametr(adress)!=0){
        name=model->getParametr(adress)->Name()+" (0"+QString::number(adress,8)+")";
    }
    model->removeObserver(discr_models[forms.at(index)->adress()]);
    delete discr_models[forms.at(index)->adress()];
    discr_models.remove(forms.at(index)->adress());
    forms.at(index)->setModel(mod,name);
    discr_models[adress]=mod;
    model->registerObserver(mod);
    forms.at(index)->LabelHasWord()->setAdress(adress);
}

bool MdiForm::containsDiscrModel(int adress)
{
    return discr_models.contains(adress);
}

int MdiForm::countDiscrTables() const
{
    return forms.count();
}

int MdiForm::countDiscrModels() const
{
    return discr_models.count();
}

void MdiForm::deleteDiscrTable(int adress)
{
    model->removeObserver(discr_models[adress]);
    foreach (MdiFormDiscr* f, forms) {
        if(f->adress()==adress){
            model->removeObserver(f->LabelHasWord());
            delete f;
            forms.removeOne(f);
        }
    }
    delete discr_models[adress];
    discr_models.remove(adress);
}

int MdiForm::index() const
{
    return i;
}

MdiForm::~MdiForm()
{
    emit MdiFormDeleted(i);
    foreach(ModelDiscrTable *tmod,discr_models)
        delete tmod;
    delete ui;
}

void MdiForm::resizeTableToContent()
{
    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();
}
void MdiForm::setVisibleDiscrTables(bool visible)
{
    if(!visible){
        QList<int> list;
        list<<100<<0;
        ui->splitter->setSizes(list);
    }else if(visible){
        QList<int> list;
        list<<ui->tableView->width()/2<<ui->tableView->width()/4;
        ui->splitter->setSizes(list);
    }
}

void MdiForm::createActions()
{
    actionVisibleValue=new QAction(QObject::tr("Значение"),ui->tableView->horizontalHeader());
    actionVisibleValue->setCheckable(true);
    actionVisibleValue->setChecked(true);

    actionVisibleDimension=new QAction(QObject::tr("Размерность"),ui->tableView->horizontalHeader());
    actionVisibleDimension->setCheckable(true);
    actionVisibleDimension->setChecked(true);

    actionVisibleMS=new QAction(QObject::tr("Матрица состояния"),ui->tableView->horizontalHeader());
    actionVisibleMS->setCheckable(true);
    actionVisibleMS->setChecked(true);

    actionVisibleAdress=new QAction(QObject::tr("Адрес"),ui->tableView->horizontalHeader());
    actionVisibleAdress->setCheckable(true);
    actionVisibleAdress->setChecked(true);

    actionVisibleUnpack=new QAction(QObject::tr("Все слово"),ui->tableView->horizontalHeader());
    actionVisibleUnpack->setCheckable(true);
    actionVisibleUnpack->setChecked(true);

    actionBuildGraf=new QAction(QObject::tr("Вывести на график"),ui->tableView);
}

void MdiForm::connectActionsToSlots()
{
    connect(actionVisibleAdress,SIGNAL(triggered(bool)),this,SLOT(setVisibleAdress(bool)));
    connect(actionVisibleDimension,SIGNAL(triggered(bool)),this,SLOT(setVisibleDimension(bool)));
    connect(actionVisibleValue,SIGNAL(triggered(bool)),this,SLOT(setVisibleValue(bool)));
    connect(actionVisibleMS,SIGNAL(triggered(bool)),this,SLOT(setVisibleMS(bool)));
    connect(actionVisibleUnpack,SIGNAL(triggered(bool)),this,SLOT(setVisibleUnpack(bool)));
    connect(actionBuildGraf,SIGNAL(triggered()),this,SLOT(actionGraf()));
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

int ModelTable::adressOfRow(int row) const
{
    QModelIndex index=this->index(row,visible_columns.indexOf(Ui::TABLE_ADRESS));
    int x=dat[index].toInt();
    int y,s=0,i=0;
    while(x){//Переводим из восьмеричной системы в десятичную
        y=x;
        x /= 10;
        y=(y-x*10)*pow(8,i++);
        s+=y;
    }
    return s;
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
        names_header[count]=QString::number(count+1);
        QModelIndex index;
        //Имя параметра
        if(visible_columns.contains(Ui::TABLE_NAME)){
            index=this->index(count,visible_columns.indexOf(Ui::TABLE_NAME));
            dat[index]=map.value(adress)->FormatValue(Parametr::Format::NameParametr);
        }
        //Значение параметра
        if(visible_columns.contains(Ui::TABLE_VALUE)){
            index=this->index(count,visible_columns.indexOf(Ui::TABLE_VALUE));
            dat[index]=map.value(adress)->FormatValue(Parametr::Format::ValueParametr);
        }
        //Адресс параметра
        if(visible_columns.contains(Ui::TABLE_ADRESS)){
            index=this->index(count,visible_columns.indexOf(Ui::TABLE_ADRESS));
            dat[index]=map.value(adress)->FormatValue(Parametr::Format::Adress);
        }
        //Матрица состояния
        if(visible_columns.contains(Ui::TABLE_MS)){
            index=this->index(count,visible_columns.indexOf(Ui::TABLE_MS));
            dat[index]=map.value(adress)->FormatValue(Parametr::Format::MatrixStateParametr);
        }
        //Размерность
        if(visible_columns.contains(Ui::TABLE_DIMENSION)){
            index=this->index(count,visible_columns.indexOf(Ui::TABLE_DIMENSION));
            dat[index]=map.value(adress)->FormatValue(Parametr::Format::DimensionParametr);
        }
        //Нераспакованное слово
        if(visible_columns.contains(Ui::TABLE_UNPACK)){
            index=this->index(count,visible_columns.indexOf(Ui::TABLE_UNPACK));
            dat[index]=map.value(adress)->FormatValue(Parametr::Format::UnpackValue);
        }
        ++count;
    }
    QModelIndex topleft=this->index(0,0);
    QModelIndex bottomright=this->index(rows,columns);
    emit dataChanged(topleft, bottomright);
    //emit headerDataChanged(Qt::Vertical,0,rows);
    //emit changeContent();
}

int ModelTable::timeToUpdate()
{
    return Ui::default_time_to_update_tables;
}

void ModelTable::setVisibleHeader(bool visible, Parametr::Format f)
{
    int count=visible_columns.count();
    switch(f){
    case Parametr::Format::DimensionParametr:
        if(!visible)visible_columns.removeAt(visible_columns.indexOf(Ui::TABLE_DIMENSION));
        else if(!visible_columns.contains(Ui::TABLE_DIMENSION))
            visible_columns.insert(2,Ui::TABLE_DIMENSION);
        break;
    case Parametr::Format::Adress:
        if(!visible)visible_columns.removeAt(visible_columns.indexOf(Ui::TABLE_ADRESS));
        else if(!visible_columns.contains(Ui::TABLE_ADRESS))
            visible_columns.insert(4,Ui::TABLE_ADRESS);
        break;
    case Parametr::Format::UnpackValue:
        if(!visible)visible_columns.removeAt(visible_columns.indexOf(Ui::TABLE_UNPACK));
        else if(!visible_columns.contains(Ui::TABLE_UNPACK))
            visible_columns.insert(5,Ui::TABLE_UNPACK);
        break;
    case Parametr::Format::MatrixStateParametr:
        if(!visible)visible_columns.removeAt(visible_columns.indexOf(Ui::TABLE_MS));
        else if(!visible_columns.contains(Ui::TABLE_MS))
            visible_columns.insert(3,Ui::TABLE_MS);
        break;
    case Parametr::Format::ValueParametr:
        if(!visible)visible_columns.removeAt(visible_columns.indexOf(Ui::TABLE_VALUE));
        else if(!visible_columns.contains(Ui::TABLE_VALUE))
            visible_columns.insert(1,Ui::TABLE_VALUE);
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

void MdiForm::on_splitter_splitterMoved(int pos, int index)
{

}

void MdiForm::setVisibleAdress(bool f)
{
    table->setVisibleHeader(f,Parametr::Adress);
}

void MdiForm::setVisibleDimension(bool f)
{
    table->setVisibleHeader(f,Parametr::DimensionParametr);
}

void MdiForm::setVisibleValue(bool f)
{
    table->setVisibleHeader(f,Parametr::ValueParametr);
}

void MdiForm::setVisibleMS(bool f)
{
    table->setVisibleHeader(f,Parametr::MatrixStateParametr);
}

void MdiForm::setVisibleUnpack(bool f)
{
    table->setVisibleHeader(f,Parametr::UnpackValue);
}

void MdiForm::actionGraf()
{
    int adress=table->adressOfRow(ui->tableView->selectionModel()->currentIndex().row());
    emit buildGrafik(adress);
}




