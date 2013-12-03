#include <iostream>
#include <ctime>
#include <cstdlib>
#include "subjectblock.h"
#include "dice.h"
#include "qgameitem.h"
#include <QMessageBox>
#include "localgame.h"
#include "sellpopup.h"

// Constructor & Destructor
SubjectBlock::~SubjectBlock()
{

}


// Methods
SubjectBlock::SubjectBlock(QGameItem * parent,
                           SubjectType::Type type, QString subject_name, int cost)
    : Block(parent)
{
    department = type;
    this->subject_name = subject_name;
    owner = NULL;
    this->value = cost;
}

SubjectType::Type SubjectBlock::getDept() const
{
    return department;
}


QString SubjectBlock::getName() const
{
    return subject_name;
}

int SubjectBlock::getGrade() const
{
    return grade;
}

int SubjectBlock::getBuyOutPrice(){
    int buyoutprice = value;
    //calculate
    return buyoutprice;
}

int SubjectBlock::getPenalyCost(){
    int p = penaltycost;
    //calculate
    return p;
}

void SubjectBlock::enter(Player* player)
{
    QMessageBox mbox;
    mbox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    mbox.setDefaultButton(QMessageBox::Ok);
    if(owner == NULL)   //빈블럭
    {
        if(player->getEnergy() >= value){

            mbox.setText("이 과목을 수강하시겠습니까?");
            mbox.exec();
            int userselect = mbox.exec();

            if(userselect==QMessageBox::ok)   //if buy
            {
                player->buyBlock(this);
            }
            LocalGame::getInst()->turnOver();
            return;
        }
    }
    else if(owner==player)  //자신의 블럭
    {
        mbox.setText("이 과목을 재수강하시겠습니까?");
        int userselect = mbox.exec();
        if(userselect== QMessageBox::Ok)   //if yes
        {
            decideGrade();
        }

        LocalGame::getInst()->turnOver();
        return;
    }
    else    //타인의 블럭
    {
        if(getPenalyCost()<player->getEnergy())
        {
            player->payEnergy(penaltycost);
            this->owner->giveEnergy(penaltycost);

            if(player->getEnergy() > getBuyOutPrice()){
                mbox.setText("블럭을 인수하시겠습니까?");
                int userselect = mbox.exec();
                if(userselect == QMessageBox::Ok)//buy the block;
                {
                    int priceofownedsubject=value+penaltycost*2;//value나 cost나.... 합치는 작업 해줘야할듯!
                    this->owner->removeBlock(this);
                    player->pushBlock(this);
                    player->addTotalOwnSubjectEnergy(value);
                    this->owner->addTotalOwnSubjectEnergy(-value);
                    player->setEnergy(player->getEnergy()-priceofownedsubject);
                    this->owner->setEnergy(this->owner->getEnergy()+priceofownedsubject);
                }
            }
            return;
        }
        else{//블럭을 팔거나 파산한다.
            //popup gogo
            if(player->getAssetValue() > penaltycost){

                Sellpopup * popup = Sellpopup();
                popup->show();

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

void SubjectBlock::mousePressEvent(QGraphicsSceneMouseEvent *event){
    qDebug() << "subject name:" << this->subject_name;
}
