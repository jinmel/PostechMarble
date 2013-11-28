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

    int grade;
    int cost;

public:
    SubjectBlock(SubjectType type,std::string subject_name,int cost);
    virtual ~SubjectBlock();
    SubjectType::Type getType() const;
    virtual void enter(Player* player);
    void decideGrade();

};
