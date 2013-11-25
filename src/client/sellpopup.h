#ifndef SELLPOPUP_H
#define SELLPOPUP_H

#include <QWidget>

namespace Ui {
class sellpopup;
}

class sellpopup : public QWidget
{
    Q_OBJECT

public:
    explicit sellpopup(QWidget *parent = 0);
    ~sellpopup();

private:
    Ui::sellpopup *ui;
};

#endif // SELLPOPUP_H
