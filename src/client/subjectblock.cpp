#include <iostream>
#include <ctime>
#include <cstdlib>
#include "subjectblock.h"
#include "dice.h"
#include "qgameitem.h"

// Constructor & Destructor
SubjectBlock::~SubjectBlock()
{

}


// Methods
SubjectBlock::SubjectBlock(QGameItem * parent,
                           SubjectType::Type type, std::string subject_name, int cost)
    : Block(parent)
{
    department = type;
    this->subject_name = subject_name;
    owner = NULL;
    this->cost = cost;
}

SubjectType::Type SubjectBlock::getType() const
{
    return department;
}

void SubjectBlock::enter(Player* player)
{
    if(owner == NULL)   //빈블럭
    {
        if(player->getEnergy()>=cost){


            qDebug()<<"Do you want to buy this subject?"<<endl;
            int userselect;
            qDebug()<<"1.Yes    2.No"<<endl;
            qDebug()<<">>";
            //cin<<userselect;

            if(userselect==1)   //if buy
            {
                player->buyBlock(this);

            }
            else                //not buy
                return;
        }
    }
    
    else if(owner==player)  //자신의 블럭
    {
        qDebug()<<"Do you want to take this subject again?"<<endl;//재수강 여부 확인
        int userselect;
        qDebug()<<"1.yes    2.no";
        //cin>>userselect;
        if(userselect==1)   //if yes
        {
            decideGrade();
        }
        else//if no
            return;

    }
    else    //타인의 블럭
    {
        if(paneltycost>player->getEnergy())
        {
            player->payEnergy(paneltycost);
            this->owner->paidEnergy(paneltycost);

            qDebug()<<"Do you want to buy the block?"<<endl;
            qDebug()<<"1.yes    2.no"<<endl;
            int userselect;
            if(userselect==1)//buy the block;
            {
                int priceofownedsubject=value+paneltycost*2;//value나 cost나.... 합치는 작업 해줘야할듯!
                this->owner->removeBlock(this);
                player->pushBlock(this);
                player->addTotalOwnSubjectEnergy(value);
                this->owner->addTotalOwnSubjectEnergy(-value);
                player->setEnergy(player->getEnergy()-priceofownedsubject);
                this->owner->setEnergy(this->owner->getEnergy()+priceofownedsubject);

            }
            else//not buy the block
            {return;}



        }
        else{//블럭을 팔거나 파산한다.

            if(paneltycost > player->getTotalOwnSubjectEnergy())//가진 모든 과목을 팔아도 안될때 -> bankrupt
            {
                player->setBankrupt(true);
            }
            else
            {

                //과목을 팔도록 한다.
                //사용자로부터 팔 과목을 선택받는다... panelty cost보다 높은 금액만큼의 과목..
                std::list<Block*> delete_blocks;//블럭을 선택받아온다....


                /*while(!delete_blocks->empty())
               {  player->sellBlock(//block); }for문 돌려서 다 팔아줘야할듯~
            */
            }

        }



    }
}

    void SubjectBlock::decideGrade(){
        srand((unsigned)time(NULL));
        int randomvalue;
        randomvalue = rand() % 100 + 1;

        if(randomvalue<=20)
            grade = 4;      //A
        else if(randomvalue<=60)
            grade = 3;      //B
        else
            grade = 2;      //C

    }
