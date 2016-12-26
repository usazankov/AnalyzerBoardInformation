#ifndef MDIFORMDISCR_H
#define MDIFORMDISCR_H

#include <QWidget>

namespace Ui {
class MdiFormDiscr;
}

class MdiFormDiscr : public QWidget
{
    Q_OBJECT

public:
    explicit MdiFormDiscr(QWidget *parent = 0);
    ~MdiFormDiscr();

private:
    Ui::MdiFormDiscr *ui;
};

#endif // MDIFORMDISCR_H
