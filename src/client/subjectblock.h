#ifndef SUBJECTBLOCK_H
#define SUBJECTBLOCK_H

enum Department {CSE, ME, MATH, EECE, PHYS. BIOLOTY, CHEM, MSE};


class SubjectBlock : public Block
{

private:
    Department	department;
    String		subject_name;//æÍ∞° string¿Ã ø÷ æ»¥Ô?;;;;
    Player*		owner;

    int grade;
    int cost;

public:
    SubjectBlock(){}//constructor
    void enter();


};

#endif // SUBJECTBLOCK_H
