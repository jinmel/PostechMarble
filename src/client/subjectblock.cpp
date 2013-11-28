#include <iostream>
#include <time>
#include <cstdlib>
#include "subjectblock.h"
#include "dice.h"

// Constructor & Destructor
SubjectBlock::SubjectBlock()
{
    qDebug()<<"Subject Block constructed."<<endl;
    owner = NULL;
}


SubjectBlock::~SubjectBlock()
{
    qDebug()<<"Subject Block destroyed."<<endl;
}


// Methods
 void SubjectBlock::setSubjectBlock(SubjectType::Type blockdepartment, std::string subjectname){
     department=blockdepartment;
     subject_name=subjectname;
 }
SubjectType::Type SubjectBlock::getType() const
{
    return department;
}

void SubjectBlock::enter(Player* player)
{
    if(owner==NULL)//빈블럭
    {
        if(player->getEnergy()>=cost){


            qDebug()<<"Do you want to buy this subject?"<<endl;
            int userselect;
            qDebug()<<"1.Yes    2.No"<<endl;
            qDebug()<<">>";
            //cin<<userselect;

            if(userselect==1)//if buy
            {
                player->buyBlock(this);

            }
            else//not buy
            {return;}
        }
    }
    else if(owner==player)//자신의 블럭
    {
        qDebug()<<"Do you want to take this subject again?"<<endl;//재수강 여부 확인
        int userselect;
        qDebug()<<"1.yes    2.no";
        //cin>>userselect;
        if(userselect==1)//if yes
        {
            decideGrade();
        }
        else//if no
            return;

    }
    else//타인의 블럭
    {
        if(paneltycost>player->getEnergy())
        {


        }
        else{


        }



    }
}

    void SubjectBlock::decideGrade(){
        srand((unsigned)time(NULL));
        int randomvalue;
        randomvalue = rand() % 100 + 1;

        if(randomvalue<=20)
        {grade = 4;}//A
        else if(randomvalue<=60)
        {grade = 3;}//B
        else
        {grade = 2;}//C

    }
