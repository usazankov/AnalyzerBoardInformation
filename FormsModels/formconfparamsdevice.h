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
#include <QFile>
#include <QFileDialog>
#include <typeinfo>
#include "settingsdevice.h"
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
    void insertChannel(const QString &name,int i);
    void deleteChannel(int i);
    SettingsDevice* conf(int i)const;
    void saveToFile(int i, const QString &filePath);
    QList<ConfParametr*> openFile(const QString &filePath);
    bool ContainsChannel(int i)const;
    bool ContainsChannel(const QString &name)const;
    bool ChannelsIsEmpty()const;
    void renameChannel(const QString &newname, int i);
    ~FormConfParamsDevice();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_comboNameChannel_activated(int index);
    void on_comboNameChannel_currentIndexChanged(const QString &arg1);
    void on_tableView_clicked(const QModelIndex &index);
    void changed_selection(const QModelIndex &index, const QModelIndex &previous);
    void commit_type_param();
    void on_add_state();
    void on_del_state();
    void on_pushButton_4_clicked();
    void on_pushButton_3_clicked();

public slots:
    void change_least_bit(int bit);
    void change_most_bit(int bit);
    void change_unpack_const(double uc);
private:
    void updateItemsComboBox();
    Ui::FormConfParamsDevice *ui;
    QMap<int, ModelConfParams*> models;
    QMap<int, int> last_selected_index;
    int cout_channel;
    int current_index;
    QMap<int, QString> channels;
    QStackedWidget *stwidget;
    FormDecParam *formDec;
    FormDiscrParam *formDiscr;
};

#endif // FORMCONFPARAMSDEVICE_H
