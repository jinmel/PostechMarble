#pragma once
#include <QString>
#include "player.h"
#include "types.h"
#include "block.h"
#include <QGraphicsPixmapItem>
#include <QMediaPlayer>

class Player;

class SubjectBlock : public Block
{
public:
    enum Grade{
        A = 4,
        B = 3,
        C = 2,
        NONE =1
    };
private:
    SubjectType::Type       department;
    QString                 subject_name;
    Player*                 owner;
    int                     cost;
    Grade                   grade; //4->A 3->B 2->C
    QGraphicsPixmapItem *   grade_image;
    QMediaPlayer*           effect_sound;

public:
    SubjectBlock(QGameItem* parent,
                 SubjectType::Type type, QString subject_name, int cost);
    virtual ~SubjectBlock();
    SubjectType::Type getDept() const;
    QString getName() const;
    Grade getGrade() const;
    void setGrade(Grade grade);
    int getCost() const;
    virtual void enter(Player* player);
    void decideGrade();
    int getBuyOutPrice(); //인수할때 가격
    int getPenaltyCost(); //남이 수강한 땅을 밟았을 때 내야 하는 통행료
    int getSellCost(); //팔 때 가격
    void setOwner(Player * player);
    Player * getOwner();
    void setGradeImage(Grade grade);

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);

};
