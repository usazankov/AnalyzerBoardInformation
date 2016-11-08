#ifndef FORMCONFPARAMSDEVICE_H
#define FORMCONFPARAMSDEVICE_H

#include <QDialog>
#include "modelconfparams.h"
#include <QItemDelegate>
#include <QComboBox>
#include <QLineEdit>
namespace Ui {
class FormConfParamsDevice;
}

class ComboBoxDelegate: public QItemDelegate{
    Q_OBJECT
public:
    ComboBoxDelegate(const QVector<QString> &items,QObject *parent = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
private:
    QVector<QString> items;
    int current_index;
};

class FormConfParamsDevice : public QDialog
{
    Q_OBJECT

public:
    explicit FormConfParamsDevice(QWidget *parent = 0);
    ~FormConfParamsDevice();

private slots:
    void on_pushButton_clicked();

private:
    Ui::FormConfParamsDevice *ui;
    ModelConfParams *model;
};

#endif // FORMCONFPARAMSDEVICE_H
