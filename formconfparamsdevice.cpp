#include "formconfparamsdevice.h"
#include "ui_formconfparamsdevice.h"

FormConfParamsDevice::FormConfParamsDevice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FormConfParamsDevice)
{
    ui->setupUi(this);

    QVector<QString> list;
    list.push_back("Десятичный");
    list.push_back("Дискретный");
    list.push_back("Дискретно-десятичный");
    list.push_back("Двоично-десятичный");
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    ui->tableView->horizontalHeader()->setDefaultSectionSize(135);
    ui->tableView->horizontalHeader()->setMinimumSectionSize(135);
    ui->tableView->horizontalHeader()->setMaximumSectionSize(180);
    ComboBoxDelegate *del=new ComboBoxDelegate(list,this);
    ui->tableView->setItemDelegateForColumn(3,del);
    stwidget=new QStackedWidget(ui->groupBox_2);
    formDec=new FormDecParam(ui->groupBox_2);
    connect(del,SIGNAL(commitData(QWidget*)),this,SLOT(commit_type_param()));
    formDec->close();
    formDiscr=new FormDiscrParam(ui->groupBox_2);
    connect(formDiscr->ButtonAdd(),SIGNAL(clicked()),this,SLOT(on_add_state()));
    connect(formDiscr->ButtonDel(),SIGNAL(clicked()),this,SLOT(on_del_state()));
    formDiscr->close();
    stwidget->addWidget(formDec);
    stwidget->addWidget(formDiscr);
    stwidget->setVisible(false);
    ui->verticalLayout_4->addWidget(stwidget);
    connect(formDec,SIGNAL(changeUnpackConst(double)),this, SLOT(change_unpack_const(double)));
    connect(formDec,SIGNAL(changeLeastBit(int)),this, SLOT(change_least_bit(int)));
    connect(formDec,SIGNAL(changeMostBit(int)),this, SLOT(change_most_bit(int)));

}

void FormConfParamsDevice::insertChannel(const QString &name, int index)
{
    if(!channels.contains(index)){
        channels[index]=name;
        ModelConfParams* model = new ModelConfParams();
        models[index]=model;
        last_selected_index[index]=0;
        connect(model,SIGNAL(changeContent()),ui->tableView,SLOT(resizeColumnsToContents()));
        current_index=index;
        ++cout_channel;
        updateItemsComboBox();
    }
}

void FormConfParamsDevice::deleteChannel(int index)
{
    channels.remove(index);
    last_selected_index.remove(index);
    --cout_channel;
    updateItemsComboBox();
}

QList<ConfParametr *> FormConfParamsDevice::conf(int index) const
{
    return models[index]->getConfParametrs();
}


void FormConfParamsDevice::saveToFile(int index, const QString &filePath)
{
    cout<<"Сохранение параметров в файл"<<endl;
    QFile file(filePath);
    if(!file.open(QIODevice::WriteOnly)){
        cout<<"Невозможно открыть файл\n";return;
    }
    QDataStream stream_file(&file);
    QList<ConfParametr*> list=*(models[index]->getConfParametrsPtr());
    int i=1;
    foreach (ConfParametr* item, list) {
        TypeParametr type=item->getType();
        stream_file<<type;
        switch (type) {
        case DEC:
            stream_file<<*(dynamic_cast<ConfDecParametr*>(item));
            break;
        case DISCR:
            stream_file<<*(dynamic_cast<ConfDiscrParametr*>(item));
            break;
        case DISCR_DEC:

            break;
        case DD:

            break;
        default:

            break;
        }

    }
    file.close();
}

QList<ConfParametr *> FormConfParamsDevice::openFile(const QString &filePath)
{
    QFile file(filePath);
    QList<ConfParametr*> *list=new QList<ConfParametr*>();
    if(!file.open(QIODevice::ReadOnly)){
        cout<<"Невозможно открыть файл\n";return *list;
    }
    QDataStream stream_file(&file);
    while(!stream_file.atEnd()){
        int i;
        stream_file>>i;
        TypeParametr type=ConfParametr::toTypeParametr(i);
        ConfParametr *p;
        switch (type) {
        case DEC:{
            ConfDecParametr *p=new ConfDecParametr();
            stream_file>>*(p);
            list->push_back(p);
            break;
        }
        case DISCR:{
            ConfDiscrParametr *p=new ConfDiscrParametr();
            stream_file>>*(p);
            list->push_back(p);
            break;
        }
        case DISCR_DEC:{

        }
            break;
        case DD:{

        }
            break;
        default:{
            ConfParametr *p=new ConfParametr();
            stream_file>>*(p);
            list->push_back(p);
            break;
        }
        }


    }
    file.close();
    return *list;
}

bool FormConfParamsDevice::ContainsChannel(int index) const
{
    return channels.contains(index);
}

bool FormConfParamsDevice::ContainsChannel(const QString &name) const
{
    return channels.contains(channels.key(name));
}

bool FormConfParamsDevice::ChannelsIsEmpty() const
{
    return channels.empty();
}

void FormConfParamsDevice::renameChannel(const QString &newname, int index)
{
    if(channels.contains(index)){
        channels[index]=newname;
        updateItemsComboBox();
    }
}

FormConfParamsDevice::~FormConfParamsDevice()
{
    delete ui;
}

void FormConfParamsDevice::on_pushButton_clicked()
{
    models[channels.key(ui->comboNameChannel->currentText())]->insertParam();

}

ComboBoxDelegate::ComboBoxDelegate(const QVector<QString> &items, QObject *parent):QItemDelegate(parent)
{
    foreach (QString i, items){
        this->items.push_back(i);
    }
}

QWidget *ComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &) const
{
    QComboBox *combo = new QComboBox(parent);
    for(int i = 0; i < items.size(); ++i)
    {
       combo->addItem(items[i]);
    }
    return combo;
}

void ComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    int value = index.model()->data(index, Qt::EditRole).toInt();
    comboBox->setCurrentIndex(value);
}

void ComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *combo = static_cast<QComboBox*>(editor);
    model->setData(index,combo->currentIndex(),Qt::EditRole);
}

void ComboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &) const
{
    editor->setGeometry(option.rect);
}


void FormConfParamsDevice::on_pushButton_2_clicked()
{
    int row=ui->tableView->currentIndex().row();
    models[channels.key(ui->comboNameChannel->currentText())]->delParam(row);

    if(row!=0)
        ui->tableView->selectRow(row-1);
    else if(row==0){
        ui->tableView->selectRow(row);      
    }
    if(models[channels.key(ui->comboNameChannel->currentText())]->rowCount(QModelIndex())==0)
        stwidget->setVisible(false);
}

void FormConfParamsDevice::on_comboNameChannel_activated(int index)
{

}

void FormConfParamsDevice::updateItemsComboBox()
{
    QStringList list;
    foreach (QString item, channels){
        list.append(item);
    }
    ui->comboNameChannel->clear();
    ui->comboNameChannel->insertItems(0,list);
}

void FormConfParamsDevice::on_comboNameChannel_currentIndexChanged(const QString &arg1)
{
    if(ui->tableView->selectionModel()!=Q_NULLPTR){
        last_selected_index[current_index]=ui->tableView->selectionModel()->currentIndex().row();
        disconnect(ui->tableView->selectionModel(),SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),this,SLOT(changed_selection(QModelIndex,QModelIndex)));
    }
    ui->tableView->setModel(models[channels.key(arg1)]);
    ui->tableView->selectRow(last_selected_index[channels.key(arg1)]);
    connect(ui->tableView->selectionModel(),SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),this,SLOT(changed_selection(QModelIndex,QModelIndex)));
    stwidget->setVisible(false);
    current_index=channels.key(arg1);
    if(ui->tableView->currentIndex().row()>=0)
        changed_selection(ui->tableView->currentIndex(),ui->tableView->currentIndex());
}

void FormConfParamsDevice::on_tableView_clicked(const QModelIndex &index)
{

}


void FormConfParamsDevice::changed_selection(const QModelIndex &index, const QModelIndex &previous)
{
    const ModelConfParams *model=dynamic_cast<const ModelConfParams*>(index.model());
    const ConfDecParametr *dec;
    const ConfDiscrParametr *discr;
    ModelConfDiscrParams *m;
    if(model->rowCount(QModelIndex())!=0){
        switch (model->typeParametr(index.row())){
        case DEC:
            stwidget->setVisible(true);
            stwidget->setCurrentIndex(0);
            dec=dynamic_cast<const ConfDecParametr*>(model->parametr(index.row()));
            formDec->setUnpackConst(dec->unpack);
            formDec->setLeastBit(dec->least_bit);
            formDec->setMostBit(dec->most_bit);
            break;
        case DISCR:
            discr=dynamic_cast<const ConfDiscrParametr*>(model->parametr(index.row()));
            m=const_cast<ModelConfDiscrParams*>(&(discr->model));
            formDiscr->TableView()->setModel(m);
            stwidget->setVisible(true);
            stwidget->setCurrentIndex(1);
            break;
        default:
            break;
        }
    }
}

void FormConfParamsDevice::commit_type_param()
{
    ui->tableView->selectionModel()->currentRowChanged(ui->tableView->currentIndex(),ui->tableView->currentIndex());
}

void FormConfParamsDevice::on_add_state()
{
    ModelConfParams *model=dynamic_cast<ModelConfParams*>(ui->tableView->model());
    ConfDiscrParametr *discr=dynamic_cast<ConfDiscrParametr*>(model->parametr_to_change(ui->tableView->currentIndex().row()));
    discr->model.insertParam();
}

void FormConfParamsDevice::on_del_state()
{
    ModelConfParams *model=dynamic_cast<ModelConfParams*>(ui->tableView->model());
    ConfDiscrParametr *discr=dynamic_cast<ConfDiscrParametr*>(model->parametr_to_change(ui->tableView->currentIndex().row()));

    int row=formDiscr->TableView()->currentIndex().row();
    discr->model.delParam(row);
    if(row!=0)
        formDiscr->TableView()->selectRow(row-1);
    else if(row==0)
        formDiscr->TableView()->selectRow(row);
}

void FormConfParamsDevice::change_least_bit(int bit)
{
    ModelConfParams *model=dynamic_cast<ModelConfParams*>(ui->tableView->model());
    ConfDecParametr *dec=dynamic_cast<ConfDecParametr*>(model->parametr_to_change(ui->tableView->currentIndex().row()));
    dec->least_bit=bit;
}

void FormConfParamsDevice::change_most_bit(int bit)
{
    ModelConfParams *model=dynamic_cast<ModelConfParams*>(ui->tableView->model());
    ConfDecParametr *dec=dynamic_cast<ConfDecParametr*>(model->parametr_to_change(ui->tableView->currentIndex().row()));
    dec->most_bit=bit;
}

void FormConfParamsDevice::change_unpack_const(double uc)
{
    ModelConfParams *model=dynamic_cast<ModelConfParams*>(ui->tableView->model());
    ConfDecParametr *dec=dynamic_cast<ConfDecParametr*>(model->parametr_to_change(ui->tableView->currentIndex().row()));
    dec->unpack=uc;
}

void FormConfParamsDevice::on_pushButton_4_clicked()
{
    QString str = QFileDialog::getSaveFileName(this,"Сохранить файл","","*.conf");
    if(!str.isEmpty()){
        if(!str.endsWith(".conf"))
            str.append(".conf");
        saveToFile(current_index,str);
    }
}

void FormConfParamsDevice::on_pushButton_3_clicked()
{
    QString str = QFileDialog::getOpenFileName(this, "Открыть файл", "", "*.conf");
    if(!str.isEmpty())
        models[current_index]->setConfParametrs(this->openFile(str));
}
