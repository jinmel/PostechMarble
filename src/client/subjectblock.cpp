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
    delete grade_image;
}


// Methods
SubjectBlock::SubjectBlock(QGameItem * parent,
                           SubjectType::Type type, QString subject_name, int cost)
    : Block(parent)
{
    block_type = BlockType::SUBJECT;
    department = type;
    this->subject_name = subject_name;
    owner = NULL;
    this->cost = cost;
    grade=NONE;
    grade_image = new QGraphicsPixmapItem(this);
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

SubjectBlock::Grade SubjectBlock::getGrade() const
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
    qDebug() << "subjectblock enter" << getPosition();
    qDebug() << "cost:" << cost;
    QMessageBox mbox;
    mbox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    mbox.setDefaultButton(QMessageBox::Ok);
    if(owner == NULL)   //빈블럭
    {
        if(player->getEnergy() >= cost)
        {
            mbox.setWindowTitle("과목 수강");
            mbox.setText("이 과목을 수강하시겠습니까?");
            mbox.setInformativeText("수강료: " + QString::number(cost));
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
        mbox.setWindowTitle("과목 재수강");
        mbox.setText("이 과목을 재수강하시겠습니까?");
        int userselect = mbox.exec();
        if(userselect== QMessageBox::Ok){   //if yes
            decideGrade();
        }
    }
    else    //타인의 블럭
    {
        qDebug() << "penalty!";
        if(getPenaltyCost() < player->getEnergy())
        {
            qDebug() <<"pay!";
            player->payEnergy(getPenaltyCost());
            this->owner->giveEnergy(getPenaltyCost());
            if(player->getEnergy() > getBuyOutPrice()) {
                mbox.setWindowTitle("과목 인수");
                mbox.setText("과목을 인수하시겠습니까?");
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
        else{//블럭을 팔거나 파산한다.
            //자산을 팔아서 메꿀수 있을 경우
            if(player->getAssetValue() > getPenaltyCost()){
                {
                    qDebug() << "sell asset!";
                    Sellpopup *popup = new Sellpopup(QGameItem::getWindow(), player, this);
                    popup->show(); //내부에서 매각하는것을 구현했음
                }
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

void SubjectBlock::decideGrade(){//random 받아서 20% A, 40% B, 40% C
    int randomvalue = rand() % 100 + 1;

    if(randomvalue<=20)
        grade = A;      //A
    else if(randomvalue<=60)
        grade = B;      //B
    else
        grade = C;      //C

    //set grade image
    setGradeImage(grade);
}

void SubjectBlock::setGrade(Grade grade){
    this->grade = grade;
    setGradeImage(grade);
}

void SubjectBlock::setGradeImage(Grade grade){
    switch(grade){
    case A:
        grade_image->setPixmap(QPixmap(":/images/ingame/block/Grade_A.png"));
        break;
    case B:
        grade_image->setPixmap(QPixmap(":/images/ingame/block/Grade_B.png"));
        break;
    case C:
        grade_image->setPixmap(QPixmap(":/images/ingame/block/Grade_C.png"));
        break;
    case NONE:
        grade_image->setPixmap(QPixmap());
    }
}



void SubjectBlock::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    qDebug() << "subject name: " << this->subject_name;
    Block::mousePressEvent(event);
}

void SubjectBlock::setOwner(Player *player){
    //cannot be called
    Q_ASSERT(owner == NULL);
    if(owner == NULL)
        owner = player;
}

Player * SubjectBlock::getOwner(){
    return owner;
}
