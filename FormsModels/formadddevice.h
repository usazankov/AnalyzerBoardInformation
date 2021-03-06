#ifndef FORMADDDEVICE_H
#define FORMADDDEVICE_H

#include <QDialog>
#include <iostream>
#include "ArincBoards/arincboardpci429linux.h"
#include "ArincBoards/arincboardmpc429linux.h"
#include "QPushButton"
namespace Ui {
class FormAddDevice;
}

class FormAddDevice : public QDialog
{
    Q_OBJECT
public:
    explicit FormAddDevice(QWidget *parent = 0);
    ~FormAddDevice();
    QString nameChannel();
    QString nameDevice();
    dev::TypeBoard typeDev();
    int numberChannel();
private slots:
    void on_comboTypeDev_activated(int index);
    void on_comboIndexDev_activated(int index);
    void on_comboNumberChannel_activated(int index);
private:
    Ui::FormAddDevice *ui;
    QString namedev;
    bool devOk;
};

#endif // FORMADDDEVICE_H
