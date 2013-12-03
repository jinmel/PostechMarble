#pragma once
#include <QLayout>
#include <QWidget>
#include <QCheckBox>
#include "player.h"
#include "subjectblock.h"

namespace Ui {
class Sellpopup;
}

class Sellpopup : public QWidget
{
    Q_OBJECT

public:
    //explicit Sellpopup(QWidget *parent = 0, Player *playuer, SubjectBlock *block);
    explicit Sellpopup(QWidget *parent = 0);
    ~Sellpopup();
private:
    Ui::Sellpopup *ui;
    QVBoxLayout *layout;
    QCheckBox** checks;
    SubjectBlock** blocks;
    Player *player;
    int block_num;
    int needed_value;
    QString convertDept(SubjectType::Type type);
    QString convertGrade(int grade);
private slots:
    void sell();
    void bankrupt();
    void calculate();
};
