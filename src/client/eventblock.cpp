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
    int value = rand() % 7;

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
    QMessageBox warn_box;
    warn_box.setStandardButtons(QMessageBox::Ok);
    warn_box.setDefaultButton(QMessageBox::Ok);
    warn_box.setWindowTitle("이벤트: Campus Couple");

    // 행동력 감소 + 일정 확률로 휴학 또는 61콜 이동
    if(getType() != CharacterType::OUTSIDER)
    {
        warn_box.setText("랜덤한 장소로 이동합니다.");
        // jump to gapyear
        if((rand() % 2) == 0)
            player->jumpTo(8);
        // jump to 61call
        else
            player->jumpTo(24); // 61call
    }
    else {
        warn_box.setText("당신은 아웃사이더라서 캠퍼스 커플에 면역입니다.");
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
    QMessageBox warn_box;
    warn_box.setStandardButtons(QMessageBox::Ok);
    warn_box.setDefaultButton(QMessageBox::Ok);
    warn_box.setWindowTitle("이벤트: 롤 중독");
    warn_box.setText("롤에 중독되어 에너지가 감소합니다!");
    warn_box.exec();

    // 50:50으로 행동력 증가 또는 감소, lol타입 캐릭터의 경우 항상 증가
    if(getType() == CharacterType::LOL)
        player->giveEnergy(50);
    else
    {
        if((rand() % 2) == 0){
            player->giveEnergy(50);
        }
        else{
            player->payEnergy(100);
        }
    }
    LocalGame::getInst()->turnOver();
}

void EventBlock::eatChicken(Player* player)
{
    QMessageBox warn_box;
    warn_box.setStandardButtons(QMessageBox::Ok);
    warn_box.setDefaultButton(QMessageBox::Ok);
    warn_box.setWindowTitle("이벤트: 치느님");
    warn_box.setText("치느님을 영접하여 에너지가 증가합니다!");
    warn_box.exec();
    player->giveEnergy(100);
    LocalGame::getInst()->turnOver();
}

void EventBlock::photoGenic(QGraphicsScene * scene, MainWindow * window)
{
    //팀원 사진 띄우기
    PhotoGenicItem* photogenicitem = new PhotoGenicItem(scene, window);
    photogenicitem->showPhotos();
    LocalGame::getInst()->setGameState(LocalGameState::EVENT_PHOTOGENIC);
}
