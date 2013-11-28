#include "subjectblock.h"


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
        qDebug()<<"Do you want to buy this subject?"<<endl;
        int userselect;
        qDebug()<<"1.Yes    2.No"<<endl;
        qDebug()<<">>";


        if(userselect==1)//if buy
        {//돈이 충분한가 아닌가 검사 한 후에 buy 절차

        }
        else//not buy
        {return;}
    }
    else if(owner==player)//자신의 블럭
    {
        if(player->getEnergy()>=cost)
        {
            qDebug()<<"";

        }
        else
        {

        }
    }
    else//타인의 블럭
    {


    }
}
