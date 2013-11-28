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
        if(player->getEnergy()>=cost){


            qDebug()<<"Do you want to buy this subject?"<<endl;
            int userselect;
            qDebug()<<"1.Yes    2.No"<<endl;
            qDebug()<<">>";
            //cin<<userselect;

            if(userselect==1)//if buy
            {

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
            player->buyBlock(this);
        else//if no
            return;

    }
    else//타인의 블럭
    {



    }
}
