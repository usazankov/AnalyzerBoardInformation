#ifndef FORMDECPARAM_H
#define FORMDECPARAM_H

#include <QWidget>

namespace Ui {
class FormDecParam;
}

class FormDecParam : public QWidget
{
    Q_OBJECT

public:
    explicit FormDecParam(QWidget *parent = 0);
    void setUnpackConst(double uc);
    double UnpackConst();
    void setLeastBit(int bit);
    int leastBit();
    void setMostBit(int bit);
    int mostBit();
    ~FormDecParam();
signals:
    void changeUnpackConst(double);
    void changeLeastBit(int);
    void changeMostBit(int);
private slots:
    void on_doubleSpinBox_valueChanged(double arg1);

    void on_spinBox_valueChanged(int arg1);

    void on_spinBox_2_valueChanged(int arg1);

private:
    Ui::FormDecParam *ui;
};

#endif // FORMDECPARAM_H
