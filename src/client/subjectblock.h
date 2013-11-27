#pragma once
#include <string>
#include "block.h"
#include "player.h"

class Player;

class SubjectBlock : public Block
{
public:
    enum Department {
        CSE, ME, MATH, EE, PHYS, BIO, CHEM, MSE
    };

private:
    Department      department;
    std::string     subject_name;
    Player*         owner;
    Department      subject_type;

    int grade;
    int cost;

public:
    SubjectBlock();
    virtual ~SubjectBlock();
    Department getType() const;
    virtual void enter(Player* player);
};
