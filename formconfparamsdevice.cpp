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

    formDec->close();
    formDiscr=new FormDiscrParam(ui->groupBox_2);
    formDiscr->close();
    stwidget->addWidget(formDec);
    stwidget->addWidget(formDiscr);
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
        connect(model,SIGNAL(changeContent()),ui->tableView,SLOT(resizeColumnsToContents()));
        ++cout_channel;
        updateItemsComboBox();
    }
}

void FormConfParamsDevice::deleteChannel(int index)
{
    channels.remove(index);
    --cout_channel;
    updateItemsComboBox();
}

bool FormConfParamsDevice::ContainsChannel(int index) const
{
    return channels.contains(index);
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
    else if(row==0)
        ui->tableView->selectRow(row);

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
    ui->tableView->setModel(models[channels.key(arg1)]);
}

void FormConfParamsDevice::on_tableView_clicked(const QModelIndex &index)
{
    const ModelConfParams *model=dynamic_cast<const ModelConfParams*>(index.model());
    const ConfDecParametr *dec;
        switch (model->typeParametr(index.row())){
        case DEC:
            stwidget->setCurrentIndex(0);
            dec=dynamic_cast<const ConfDecParametr*>(model->parametr(index.row()));
            formDec->setUnpackConst(dec->unpack);
            formDec->setLeastBit(dec->least_bit);
            formDec->setMostBit(dec->most_bit);
            break;
        case DISCR:
            stwidget->setCurrentIndex(1);
            break;
        default:
            break;
        }
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


