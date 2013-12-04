#include "eventblock.h"
#include "scene/ingamescene.h"
#include <ctime>
#include <iostream>
#include <QMessageBox>
#include <cstdlib>
#include "scene/ingamescene.h"
#include "localgame.h"
#include "sellpopup.h"
#include "types.h"
using namespace std;

// Constructor & Destructor
EventBlock::EventBlock(QGameItem * parent,QGraphicsScene * scene, MainWindow * window) : Block(parent)
{
    block_type = BlockType::EVENT;
}


EventBlock::~EventBlock()
{

}


// Methods
void EventBlock::enter(Player* player)
{
    checkEvent(player,this->scene(),this->getWindow());
    return;
    //checkEvent(player);
}


void EventBlock::checkEvent(Player* player,QGraphicsScene * scene, MainWindow * window)
{
    // generate random event
    int value = 0;

    switch(value) {
    case 0:
        drink(player);
        break;
    case 1:
        cc(player);
        break;
    case 2:
        takeSubject(player);
        break;
    case 3:
        loseSubject(player);
        break;
    case 4:
        lol(player);
        break;
    case 5:
        eatChicken(player);
        break;
    case 6:
        qDebug() << "photogenic";
        photoGenic(scene, window);
        break;
    }
}

void EventBlock::drink(Player* player)
{
    qDebug() << "Drink event!";
    LocalGame::getInst()->setGameState(LocalGameState::EVENT_DRINK);
}

void EventBlock::cc(Player* player)
{
    qDebug() << "CC event!";

    // 행동력 감소 + 일정 확률로 휴학 또는 61콜 이동
    if(getType() != CharacterType::OUTSIDER)
    {
        // jump to gapyear
        if((rand() % 2) == 0)
            player->jumpTo(8);

        // jump to 61call
        else
            player->jumpTo(26);
    }
}

void EventBlock::takeSubject(Player* player)
{
    QMessageBox warn_box;
    warn_box.setStandardButtons(QMessageBox::Ok);
    warn_box.setDefaultButton(QMessageBox::Ok);
    warn_box.setWindowTitle("이벤트: 과목 수강");
    warn_box.setText("수강할 과목 블럭을 선택해 주세요!");
    warn_box.exec();

    LocalGame::getInst()->setGameState(LocalGameState::EVENT_TAKE_SUBJECT);
}

void EventBlock::loseSubject(Player* player)
{
    QMessageBox warn_box;
    warn_box.setStandardButtons(QMessageBox::Ok);
    warn_box.setDefaultButton(QMessageBox::Ok);
    warn_box.setWindowTitle("이벤트: 과목 포기");
    warn_box.setText("포기할 과목 블럭을 선택해 주세요!");
    warn_box.exec();
    LocalGame::getInst()->setGameState(LocalGameState::EVENT_LOSE_SUBJECT);
}

void EventBlock::lol(Player* player)
{
    qDebug() << "LOL event!";

    // 50:50으로 행동력 증가 또는 감소, lol타입 캐릭터의 경우 항상 증가
    if(getType() == CharacterType::LOL)
        player->setEnergy(player->getEnergy() + 50); //
    else
    {
        if((rand() % 2) == 0)
            player->setEnergy(player->getEnergy() + 50); //승리
        else
            player->setEnergy(player->getEnergy() - 100); // 패배
    }
}

void EventBlock::eatChicken(Player* player)
{
    // 치느님을 영접하여 행동력 증가
    player->setEnergy(player->getEnergy() + 100);
}

void EventBlock::photoGenic(QGraphicsScene * scene, MainWindow * window)
{
    //팀원 사진 띄우기
    PhotoGenicItem* photogenicitem = new PhotoGenicItem(scene, window);
    photogenicitem->showPhotos();
    LocalGame::getInst()->turnOver();
}
