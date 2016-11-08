#include "formconfparamsdevice.h"
#include "ui_formconfparamsdevice.h"

FormConfParamsDevice::FormConfParamsDevice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FormConfParamsDevice)
{
    ui->setupUi(this);
    model=new ModelConfParams();
    ui->tableView->setModel(model);
    QVector<QString> list;
    list.push_back("Десятичный");
    list.push_back("Дискретный");
    list.push_back("Дискретно-десятичный");
    list.push_back("Двоично-десятичный");
    ui->tableView->setItemDelegateForColumn(3,new ComboBoxDelegate(list,this));
}

FormConfParamsDevice::~FormConfParamsDevice()
{
    delete ui;
}

void FormConfParamsDevice::on_pushButton_clicked()
{
    model->insertParam();
}

ComboBoxDelegate::ComboBoxDelegate(const QVector<QString> &items, QObject *parent):QItemDelegate(parent)
{
    foreach (QString i, items) {
        this->items.push_back(i);
    }
}

QWidget *ComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
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

void ComboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}

void ComboBoxDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItemV4 myOption = option;
    QString text = items[index.model()->data(index,Qt::DisplayRole).toInt()];
    myOption.text = text;
    QApplication::style()->drawControl(QStyle::CE_ItemViewItem, &myOption, painter);
}
