#include "eventblock.h"
#include "scene/ingamescene.h"
#include <ctime>
#include <iostream>
#include <cstdlib>
#include "scene/ingamescene.h"
#include "localgame.h"
#include "sellpopup.h"

using namespace std;

// Constructor & Destructor
EventBlock::EventBlock(QGameItem * parent,QGraphicsScene * scene, MainWindow * window) : Block(parent)
{
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
    qDebug() << "Take Subject";
    // 플레이어가 과목을 하나 선택한 후 buyBlock을 실행한다
    //player->addBlock();
}

void EventBlock::loseSubject(Player* player)
{
    qDebug() << "Lose Subject";
    // 플레이어가 과목 하나를 잃는다. (랜덤 or 선택)
    //player->sellBlock();
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
