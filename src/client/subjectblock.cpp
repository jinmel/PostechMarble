#include "subjectblock.h"


// Constructor & Destructor
SubjectBlock::~SubjectBlock()
{
    qDebug()<<"Subject Block destroyed."<<endl;
}


// Methods
SubjectBlock::SubjectBlock(SubjectType::Type type, std::string subject_name,int cost)
{
    qDebug()<<"Subject Block constructed."<<endl;
    department = type;
    this->subject_name=subject_name;
    owner = NULL;
    this->cost = cost;
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
