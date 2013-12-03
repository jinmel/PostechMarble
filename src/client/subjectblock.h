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
    int                 cost;
    int                 grade; //4->A 3->B 2->C
    enum Grade{
        A = 4,
        B = 3,
        C = 2
    };

public:
    SubjectBlock(QGameItem* parent,
                 SubjectType::Type type, QString subject_name, int cost);
    virtual ~SubjectBlock();
    SubjectType::Type getDept() const;
    QString getName() const;
    int getGrade() const;
    int getCost() const;
    virtual void enter(Player* player);
    void decideGrade();
    int getBuyOutPrice(); //인수할때 가격
    int getPenaltyCost(); //남이 수강한 땅을 밟았을 때 내야 하는 통행료
    int getSellCost(); //팔 때 가격
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
};
