#ifndef MDIGRAFFORM_H
#define MDIGRAFFORM_H

#include <QWidget>
#include "arincmodelinterface.h"
#include "FormsModels/arincgrafikpanel.h"
namespace Ui {
class MdiGrafForm;
}

class MdiGrafForm : public QWidget
{
    Q_OBJECT

public:
    explicit MdiGrafForm(QString title,int index, QWidget *parent = 0);
    ArincGrafikPanel* graphPanel(int adress);

    void setModel(ArincModelInterface* model);
    virtual ~MdiGrafForm();
signals:
    void deletedGrafForm(int index);
public slots:
    void addGrafik(int adress);
private:
    Ui::MdiGrafForm *ui;
    QString title;
    int index;
    ArincModelInterface* model;
    QMap<int,ArincGrafikPanel*> grafiks;
};

#endif // MDIGRAFFORM_H
