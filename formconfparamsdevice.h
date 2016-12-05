#ifndef FORMCONFPARAMSDEVICE_H
#define FORMCONFPARAMSDEVICE_H

#include <QDialog>
#include "modelconfparams.h"
#include "formdecparam.h"
#include "formdiscrparam.h"
#include <QItemDelegate>
#include <QComboBox>
#include <QLineEdit>
#include <iostream>
#include <QStackedWidget>
namespace Ui {
class FormConfParamsDevice;
class ComboBoxDelegate;
}
using namespace std;
class ComboBoxDelegate: public QItemDelegate{
    Q_OBJECT
public:
    ComboBoxDelegate(const QVector<QString> &items,QObject *parent = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &) const;
private:
    QVector<QString> items;
    int current_index;
};

class FormConfParamsDevice : public QDialog
{
    Q_OBJECT

public:
    explicit FormConfParamsDevice(QWidget *parent = 0);
    void insertChannel(const QString &name,int index);
    void deleteChannel(int index);
    bool ContainsChannel(int index)const;
    ~FormConfParamsDevice();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_comboNameChannel_activated(int index);
    void on_comboNameChannel_currentIndexChanged(const QString &arg1);
    void on_tableView_clicked(const QModelIndex &index);
public slots:
    void change_least_bit(int bit);
    void change_most_bit(int bit);
    void change_unpack_const(double uc);
private:
    void updateItemsComboBox();
    Ui::FormConfParamsDevice *ui;
    QMap<int, ModelConfParams*> models;
    int cout_channel;
    QMap<int, QString> channels;
    QStackedWidget *stwidget;
    FormDecParam *formDec;
    FormDiscrParam *formDiscr;
};

#endif // FORMCONFPARAMSDEVICE_H
