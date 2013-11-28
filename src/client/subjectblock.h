#pragma once
#include <string>
#include "block.h"
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
    SubjectBlock();
    virtual ~SubjectBlock();
    SubjectType::Type getType() const;
    virtual void enter(Player* player);
    void setSubjectBlock(SubjectType::Type blockdepartment, std::string subjectname);
};
