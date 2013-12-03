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
    explicit Sellpopup(QWidget *parent = 0);
    //explicit Sellpopup(QWidget *parent = 0, Player *player = NULL);
    ~Sellpopup();
private:
    Ui::Sellpopup *ui;
    QVBoxLayout *layout;
    QCheckBox** checks;

    QString convertDept(SubjectType::Type type);
    QString convertGrade(int grade);

public signals:
    void sell();
    void cancel();

};
