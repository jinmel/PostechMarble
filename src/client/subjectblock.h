#ifndef SUBJECTBLOCK_H
#define SUBJECTBLOCK_H

enum Department {CSE, ME, MATH, EECE, PHYS. BIOLOTY, CHEM, MSE};


class SubjectBlock : public Block
{

private:
    Department	department;
    String		subject_name;
    Player*		owner;

    int grade;
    int cost;

public:
    SubjectBlock(){}//constructor
    void enter();


};

#endif // SUBJECTBLOCK_H
