#ifndef MDIFORM_H
#define MDIFORM_H

#include <QWidget>

namespace Ui {
class mdiForm;
}

class mdiForm : public QWidget
{
    Q_OBJECT

public:
    explicit mdiForm(QWidget *parent = 0);
    ~mdiForm();

private:
    Ui::mdiForm *ui;
};

#endif // MDIFORM_H
