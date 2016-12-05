#ifndef FORMDISCRPARAM_H
#define FORMDISCRPARAM_H

#include <QWidget>

namespace Ui {
class FormDiscrParam;
}

class FormDiscrParam : public QWidget
{
    Q_OBJECT

public:
    explicit FormDiscrParam(QWidget *parent = 0);
    ~FormDiscrParam();

private:
    Ui::FormDiscrParam *ui;
};

#endif // FORMDISCRPARAM_H
