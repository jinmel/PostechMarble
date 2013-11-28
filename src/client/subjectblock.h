#pragma once
#include <string>
#include "player.h"
#include "types.h"

class Player;

class SubjectBlock : public Block
{
private:
    SubjectType::Type   department;
    std::string         subject_name;
    Player*             owner;

    int grade;          //4->A 3->B 3->C
    int cost;
    int paneltycost;    //타인이 블럭을 밟았을 때 내야 하는 금액

public:
    SubjectBlock(SubjectType type,std::string subject_name,int cost);
    virtual ~SubjectBlock();
    SubjectType::Type getType() const;
    virtual void enter(Player* player);
    void decideGrade();

};
