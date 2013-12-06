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
EventBlock::EventBlock(QGameItem * parent,QGraphicsScene * scene, MainWindow * window) : Block(parent) // event block constructor
{
    block_type = BlockType::EVENT;
}


EventBlock::~EventBlock() //event block destructor
{

}


// Methods
void EventBlock::enter(Player* player)          // player enter into event block
{
    checkEvent(player,this->scene(),this->getWindow());
    return;
    //checkEvent(player);
}

void EventBlock::checkEvent(Player* player,QGraphicsScene * scene, MainWindow * window) // there are 7 different events.
{
    // generate random event
    int value = rand() % 7;

    switch(value) {
    case 0:                                 // drink. go to firefriday block which you want
        drink(player);
        break;
    case 1:                                 // Campus couple. go to 61 call or brake semester
        cc(player);
        break;
    case 2:                                 // take one subject
        takeSubject(player);
        break;
    case 3:                                 // lose one of your subject
        loseSubject(player);
        break;
    case 4:                                 // gain or lose your energy
        lol(player);
        break;
    case 5:                                 //gain energy    
        eatChicken(player);
        break;
    case 6:                                 // surprise! our team photo
        qDebug() << "photogenic";
        photoGenic(scene, window);
        break;
    }
}

void EventBlock::drink(Player* player)      // drink
{
    qDebug() << "Drink event!";
    QMessageBox warn_box;
    warn_box.setStandardButtons(QMessageBox::Ok);
    warn_box.setDefaultButton(QMessageBox::Ok);
    warn_box.setWindowTitle("이벤트: 음주");
    warn_box.setText("음주 이벤트! 가고 싶은 술집을 선택하세요!"); // click where you want to go
    warn_box.exec();
    LocalGame::getInst()->setGameState(LocalGameState::EVENT_DRINK);
}

void EventBlock::cc(Player* player)  //Campus couple
{
    qDebug() << "CC event!";
    QMessageBox warn_box;
    warn_box.setStandardButtons(QMessageBox::Ok);
    warn_box.setDefaultButton(QMessageBox::Ok);
    warn_box.setWindowTitle("이벤트: Campus Couple");

    // 행동력 감소 + 일정 확률로 휴학 또는 61콜 이동
    if(player->getType() != CharacterType::OUTSIDER)
    {
        warn_box.setText("랜덤한 장소로 이동합니다.");
        warn_box.exec();
        // jump to gapyear
        if((rand() % 2) == 0)
            player->jumpTo(8);
        // jump to 61call
        else
            player->jumpTo(24); // 61call
    }
    else {
        warn_box.setText("당신은 아웃사이더라서 캠퍼스 커플에 면역입니다."); // if you are Outsider. you don't think about CC.
        warn_box.exec();
    }
}

void EventBlock::takeSubject(Player* player)   // You can get one of subject block.
{
    QMessageBox warn_box;
    warn_box.setStandardButtons(QMessageBox::Ok);
    warn_box.setDefaultButton(QMessageBox::Ok);
    warn_box.setWindowTitle("이벤트: 과목 수강");
    warn_box.setText("수강할 과목 블럭을 선택해 주세요!");
    warn_box.exec();

    LocalGame::getInst()->setGameState(LocalGameState::EVENT_TAKE_SUBJECT);
}

void EventBlock::loseSubject(Player* player)  // lose one of your subject
{
    QMessageBox warn_box;
    warn_box.setStandardButtons(QMessageBox::Ok);
    warn_box.setDefaultButton(QMessageBox::Ok);
    std::list<Block*> block_list = player->getBlocks();
    if(block_list.size() >0){
        warn_box.setWindowTitle("이벤트: 과목 포기");
        warn_box.setText("포기할 과목 블럭을 선택해 주세요!");
        warn_box.exec();
        LocalGame::getInst()->setGameState(LocalGameState::EVENT_LOSE_SUBJECT);
    }
    else {
        warn_box.setWindowTitle("이벤트: 과목 포기");
        warn_box.setText("포기할 과목이 없네요.");              // if you don't  have any subjects
        warn_box.exec();
        LocalGame::getInst()->turnOver();
    }
}

void EventBlock::lol(Player* player)   // playing lol
{
    QMessageBox warn_box;
    warn_box.setStandardButtons(QMessageBox::Ok);
    warn_box.setDefaultButton(QMessageBox::Ok);
    warn_box.setWindowTitle("이벤트: 롤 중독");


    // 50:50으로 행동력 증가 또는 감소, lol타입 캐릭터의 경우 항상 증가
    if(player->getType() == CharacterType::LOL){
        warn_box.setText("롤 폐인이므로 에너지가 증가합니다!");
        player->giveEnergy(50);
    }
    else
    {
        if((rand() % 2) == 0){
            warn_box.setText("롤에 승리하여 에너지가 증가합니다!");  // win the lol. gain 50 energy.
            player->giveEnergy(50);
        }
        else{
            warn_box.setText("롤에 패배하여 에너지가 감소합니다!");    // you lose the lol. lose 100 energy
            player->payEnergy(100);
        }
    }
    warn_box.exec();
    LocalGame::getInst()->turnOver();
}

void EventBlock::eatChicken(Player* player)     //ear chicken
{
    QMessageBox warn_box;
    warn_box.setStandardButtons(QMessageBox::Ok);
    warn_box.setDefaultButton(QMessageBox::Ok);
    warn_box.setWindowTitle("이벤트: 치느님");
    warn_box.setText("치느님을 영접하여 에너지가 증가합니다!");     // get energy 100
    warn_box.exec();
    player->giveEnergy(100);
    LocalGame::getInst()->turnOver();
}

void EventBlock::photoGenic(QGraphicsScene * scene, MainWindow * window)        //photogenic
{
    //팀원 사진 띄우기
    PhotoGenicItem* photogenicitem = new PhotoGenicItem(scene, window);
    photogenicitem->showPhotos();
    LocalGame::getInst()->setGameState(LocalGameState::EVENT_PHOTOGENIC);
}
