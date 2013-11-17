#pragma once
#include <string>
#include "player.h"

class Player;

class SubjectBlock : public Block
{
public:
    enum Department {
        CSE, ME, MATH, EECE, PHYS, BIOLOTY, CHEM, MSE
    };

private:
    Department      department;
    std::string     subject_name;
    Player*         owner;

    int grade;
    int cost;

public:
    SubjectBlock(int subject);//constructor
    virtual ~SubjectBlock();
    virtual void enter();

};
