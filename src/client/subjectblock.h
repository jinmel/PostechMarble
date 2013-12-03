#pragma once
#include <QString>
#include "player.h"
#include "types.h"
#include "block.h"

class Player;

class SubjectBlock : public Block
{
private:
    SubjectType::Type   department;
    QString             subject_name;
    Player*             owner;

    int grade;          //4->A 3->B 2->C
    int penaltycost;    //타인이 블럭을 밟았을 때 내야 하는 금액

public:
    SubjectBlock(QGameItem* parent,
                 SubjectType::Type type, QString subject_name, int cost);
    virtual ~SubjectBlock();
    SubjectType::Type getDept() const;
    QString getName() const;
    int getGrade() const;
    virtual void enter(Player* player);

    void decideGrade();
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
};
