#pragma once
#include <QLayout>
#include <QWidget>
#include <QCheckBox>
#include "player.h"

namespace Ui {
class Sellpopup;
}

class Sellpopup : public QWidget
{
    Q_OBJECT

public:
    explicit Sellpopup(QWidget *parent = 0, Player *player);
    ~Sellpopup();
private:
    Ui::Sellpopup *ui;
    QVBoxLayout *layout;
    QCheckBox* blocks;
};
