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
    cost = cost;
}

int SubjectBlock::getCost() const{
    return cost;
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
    return cost + getPenaltyCost() * 2;
}


int SubjectBlock::getPenaltyCost(){
    if(grade == A)
        return int(cost * 0.8);
    else if(grade == B)
        return int(cost * 0.4);
    else if(grade == C)
        return int(cost * 0.2);
}


int SubjectBlock::getSellCost(){
    return getBuyOutPrice() /2;

}


void SubjectBlock::enter(Player* player)
{
    QMessageBox mbox;
    mbox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    mbox.setDefaultButton(QMessageBox::Ok);
    if(owner == NULL)   //빈블럭
    {
        if(player->getEnergy() >= cost)
        {
            mbox.setText("이 과목을 수강하시겠습니까?");
            mbox.setInformativeText("수강료:" + QString::number(cost));
            mbox.exec();
            int userselect = mbox.exec();
            if(userselect==QMessageBox::Ok)   //if buy
            {
                player->payEnergy(cost);
                player->addBlock(this);
                decideGrade();
            }
        }
    }
    else if(owner==player)  //자신의 블럭
    {
        mbox.setText("이 과목을 재수강하시겠습니까?");
        int userselect = mbox.exec();
        if(userselect== QMessageBox::Ok){   //if yes
            decideGrade();
        }
    }
    else    //타인의 블럭
    {
        if(getPenaltyCost() < player->getEnergy())
        {
            player->payEnergy(getPenaltyCost());
            this->owner->giveEnergy(getPenaltyCost());
            if(player->getEnergy() > getBuyOutPrice()){
                mbox.setText("블럭을 인수하시겠습니까?");
                int userselect = mbox.exec();
                if(userselect == QMessageBox::Ok)//buy the block;
                {
                    this->owner->removeBlock(this);
                    this->owner->giveEnergy(getBuyOutPrice());
                    player->payEnergy(getBuyOutPrice());
                    player->addBlock(this);
                }
            }
        }
        else {//블럭을 팔거나 파산한다.
            //자산을 팔아서 메꿀수 있을 경우
            if(player->getAssetValue() > getPenaltyCost()){

                Sellpopup *popup = new Sellpopup(QGameItem::getWindow(), player, this);
                popup->show(); //내부에서 매각하는것을 구현했음
            }
            //소 팔고 외양간 팔아도 파산 ㅠㅠ
            else {
                player->setBankrupt();
            }
        }
    }
    LocalGame::getInst()->turnOver();
    return;
}

void SubjectBlock::decideGrade(){
    srand((unsigned)time(NULL));
    int randomvalue;
    randomvalue = rand() % 100 + 1;

    if(randomvalue<=20)
        grade = A;      //A
    else if(randomvalue<=60)
        grade = B;      //B
    else
        grade = C;      //C
}

void SubjectBlock::mousePressEvent(QGraphicsSceneMouseEvent *event){
    qDebug() << "subject name:" << this->subject_name;
}
