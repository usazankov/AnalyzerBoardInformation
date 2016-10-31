#ifndef FORMCONFPARAMSDEVICE_H
#define FORMCONFPARAMSDEVICE_H

#include <QDialog>

namespace Ui {
class FormConfParamsDevice;
}

class FormConfParamsDevice : public QDialog
{
    Q_OBJECT

public:
    explicit FormConfParamsDevice(QWidget *parent = 0);
    ~FormConfParamsDevice();

private:
    Ui::FormConfParamsDevice *ui;
};

#endif // FORMCONFPARAMSDEVICE_H
