#ifndef FORMDISCRPARAM_H
#define FORMDISCRPARAM_H

#include <QWidget>
#include <QTableView>
#include <QPushButton>
namespace Ui {
class FormDiscrParam;
}

class FormDiscrParam : public QWidget
{
    Q_OBJECT
public:
    explicit FormDiscrParam(QWidget *parent = 0);
    QTableView* TableView();
    QPushButton* ButtonAdd();
    QPushButton* ButtonDel();
    ~FormDiscrParam();

private:
    Ui::FormDiscrParam *ui;
};

#endif // FORMDISCRPARAM_H
