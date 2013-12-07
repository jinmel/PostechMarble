#include <iostream>
#include <ctime>
#include <cstdlib>
#include "subjectblock.h"
#include "dice.h"
#include "qgameitem.h"
#include <QMessageBox>
#include "localgame.h"
#include "sellpopup.h"
#include <QFileInfo>

// Constructor & Destructor
SubjectBlock::~SubjectBlock()  //Destructor
{
    delete grade_image;
}


// Methods
SubjectBlock::SubjectBlock(QGameItem * parent,
                           SubjectType::Type type, QString subject_name, int cost)      //constructor
    : Block(parent)
{
    block_type = BlockType::SUBJECT;
    department = type;
    this->subject_name = subject_name;
    owner = NULL;
    this->cost = cost;
    grade=NONE;
    grade_image = new QGraphicsPixmapItem(this);
    effect_sound = new QMediaPlayer();
}

//public method
int SubjectBlock::getCost() const{          //get block's cost
    return cost;
}

SubjectType::Type SubjectBlock::getDept() const     //get subjects department
{
    return department;
}

QString SubjectBlock::getName() const           //get subject name
{
    return subject_name;
}

SubjectBlock::Grade SubjectBlock::getGrade() const      //get subject grade
{   
    return grade;
}

int SubjectBlock::getBuyOutPrice(){                     //buy other's  subject block. price : orginal cost + 2*penalty
    return cost + getPenaltyCost();
}


int SubjectBlock::getPenaltyCost(){         // pay penalty. penalty changes up to grade.
    if(grade == A)
        return int(cost * 2.0);             // if grade A , penalty = 2.0 *cost
    else if(grade == B)
        return int(cost * 1.5);             // if B, 1.5 cost
    else if(grade == C)
        return int(cost * 1.0);             //if C, 1.0 cost
    else
        return 0;
}


int SubjectBlock::getSellCost(){            // sell price : half of the price can buy the block possessed by ohter.
    return getBuyOutPrice() /2;
}


void SubjectBlock::enter(Player* player)        // player enter subject block
{
    qDebug() << "subjectblock enter" << getPosition();
    qDebug() << "cost:" << cost;
    qDebug() << "player" << player->getId();

    if(subject_name == "객체지향프로그래밍") {
        effect_sound->setMedia(QUrl::fromLocalFile(QFileInfo("sound/prof_voice.wav").absoluteFilePath()));
        effect_sound->play();            // special sounds for OOP
    }

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

            if(userselect==QMessageBox::Ok)    //if buy
            {
                player->payEnergy(cost);
                player->addBlock(this);
                decideGrade();
            }
        }
        LocalGame::getInst()->turnOver();
    }
    else if(owner==player)  //자신의 블럭
    {
        mbox.setWindowTitle("과목 재수강");
        mbox.setText("이 과목을 재수강하시겠습니까?");
        int userselect = mbox.exec();
        if(userselect== QMessageBox::Ok){   //if yes
            decideGrade();
        }
        LocalGame::getInst()->turnOver();
    }
    else    //타인의 블럭
    {
        qDebug() << "penalty!";
        if(getPenaltyCost() < player->getEnergy())  // if you have enough energy, you can take other's subject block
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
                    // play sound
                    QString sound_path="sound/subject_";
                    if((rand() % 2) == 0)
                        sound_path += "boy.wav";
                    else
                        sound_path += "girl.wav";

                    effect_sound->setMedia(QUrl::fromLocalFile(QFileInfo(sound_path).absoluteFilePath()));
                    effect_sound->play();

                    this->owner->giveEnergy(getBuyOutPrice());
                    this->owner->removeBlock(this);
                    player->payEnergy(getBuyOutPrice());
                    player->addBlock(this);
                    decideGrade();
                }
            }
            LocalGame::getInst()->turnOver();
        }
        else{
            //블럭을 팔거나 파산한다.
            //자산을 팔아서 메꿀수 있을 경우
            if(player->getAssetValue() > getPenaltyCost()){
                    qDebug() << "sell asset!";
                    Sellpopup *popup = new Sellpopup(QGameItem::getWindow(), player, this->getPenaltyCost());
                    popup->show(); //내부에서 매각하는것을 구현했음
            }
            //소 팔고 외양간 팔아도 파산 ㅠㅠ
            else {
                player->setBankrupt();
                LocalGame::getInst()->turnOver();
            }
        }
    }
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

void SubjectBlock::setGrade(Grade grade){  // set grade
    this->grade = grade;
    setGradeImage(grade);
}

void SubjectBlock::setGradeImage(Grade grade){          // set gradge image
    QString img_path = ":/images/ingame/block/";

    img_path += QString::number(owner->getId());     
    //qDebug() << img_path;
    switch(grade){                                 
    case A:
        grade_image->setPixmap(img_path + QString("A.png"));        
        break;
    case B:
        grade_image->setPixmap(img_path + QString("B.png"));
        break;
    case C:
        grade_image->setPixmap(img_path + QString("C.png"));
        break;
    case NONE:
        grade_image->setPixmap(QPixmap());
    }

    int zone = position /8;

    if(zone == 0 || zone ==2){                                          //image position setting
        QTransform rotate;
        rotate.rotate(90);
        grade_image->setPixmap(grade_image->pixmap().transformed(rotate));
    }

    //qDebug() << grade_image->pixmap().size();
    switch(zone){
        case 0:
            grade_image->setPos(QPointF(30,7));
            break;
        case 1:
            grade_image->setPos(QPointF(20,13));
            break;
        case 2:
            grade_image->setPos(QPointF(70,7));
            break;
        case 3:
            grade_image->setPos(QPointF(20,48));
            break;
    }
}



void SubjectBlock::mousePressEvent(QGraphicsSceneMouseEvent *event) {       // mouse click
    qDebug() << "subject name: " << this->subject_name;
    Block::mousePressEvent(event);
}

void SubjectBlock::setOwner(Player *player){            // set subject's owner
    owner = player;
}

Player * SubjectBlock::getOwner(){                      //get subject's owner
    return owner;
}
