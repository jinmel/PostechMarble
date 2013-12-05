#include <QDebug>
#include <iostream>
#include "block.h"
#include "cornerblock.h"
#include "player.h"
#include "dice.h"
#include "localgame.h"
#include <QMessageBox>

using namespace std;

CornerBlock::CornerBlock(QGameItem * parent,CornerType::Type type)
    : Block(parent)
{
    corner_type = type;
    block_type = BlockType::CORNER;
}

CornerBlock::~CornerBlock()
{
}


// Methods
void CornerBlock::enter(Player* player)
{
    qDebug() << "In corner block " << corner_type;
    using namespace CornerType;
    switch(corner_type)
    {
    case DORM : inDormitory(player);
        break;
    case CALLTAXI : in61Call(player);
        break;
    case BREAKSEM : inBreakSemester(player);
        break;
    case PLURAL : inPluralMajor(player);
        break;
    default : qDebug() << "CornerBlock error!" << endl;
        break;
    }
}

void CornerBlock::inDormitory(Player* player)
{
    using namespace CharacterType;
    QMessageBox warn_box;
    warn_box.setStandardButtons(QMessageBox::Ok);
    warn_box.setDefaultButton(QMessageBox::Ok);

    std::list<Block*> block_list = player->getBlocks();
    if(block_list.size() > 0){

        warn_box.setText("재수강할 과목을 선택해주세요");
        warn_box.exec();
        LocalGame::getInst()->setGameState(LocalGameState::CORNER_RETAKE_SUBJECT);
    }
    else {
        warn_box.setText("재수강할 과목이 없네요. 공부좀 하세요.");
        warn_box.exec();
        LocalGame::getInst()->turnOver();
    }
}


void CornerBlock::in61Call(Player* player)
{
    QMessageBox warn_box;
    warn_box.setStandardButtons(QMessageBox::Ok);
    warn_box.setDefaultButton(QMessageBox::Ok);
    if((rand() % 6)==0)
    {
        warn_box.setText("61콜 택시 성공! 가고 싶은 블럭을 선택하세요");
        warn_box.exec();
        LocalGame::getInst()->setGameState(LocalGameState::JUMP_PLAYER);
    }
    /*
     *moveTo 를 숫자로 넣을수 있도록 해야할듯!! 현재 있는 칸도 번호 저장해둬서 주사위 돌렸을 때 현재 숫자+주사위 눈 으로 이동하든지
    이런 경우에 바로 숫자 입력해서 이동할 수 있도록 하든지*/
    //--------->ok!
    else
    {
        warn_box.setText("61콜 택시 실패! 다음 기회에...");
        warn_box.exec();
        LocalGame::getInst()->turnOver();
    }

}

void CornerBlock::inBreakSemester(Player* player)
{
    //LocalGame에서 모두 구현되어 있음
    LocalGame::getInst()->turnOver();
    //아... 무인도에 갇힌 횟수 !!!!***********구현해야즤

    //1.원래 무인도에 있다가 다시 턴이 된 경우 -> 주사위를 굴릴 수 있게 한다.
    //2.다른 칸에 있다가 갑자기 무인도에 온 경우->바로 쉬게 한다.
    //3.휴식 횟수 새는 기능.
    //돈을 낼 수 있는지 없는지도 검사해야하는 것 아닙니까
}

void CornerBlock::inPluralMajor(Player* player)
{
    QMessageBox warn_box;
    warn_box.setStandardButtons(QMessageBox::Ok);
    warn_box.setDefaultButton(QMessageBox::Ok);
    warn_box.setText(QString("복수전공 선택! 승리하려면 두 가지 전공을 해야합니다."));
    warn_box.exec();

    switch((rand()%6)==1) {
    case 1: qDebug() <<"You have to take plural major.";
        player->setPlural(true);
        break;

    default: qDebug()<<"You don't have to take plural major.";

    }//학과 1개 독점 시에 복수전공 해제& 두개 독점 시에 승리 그리고 만약에 한개 독점 하고 두개째 도전중일 때다른 누군가가 독점된 학과를 뺏어가는 경우!?

    LocalGame::getInst()->turnOver();
}
