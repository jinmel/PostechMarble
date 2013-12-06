#include <QDebug>
#include <iostream>
#include "block.h"
#include "cornerblock.h"
#include "player.h"
#include "dice.h"
#include "localgame.h"
#include <QMessageBox>
#include <QFileInfo>

using namespace std;

CornerBlock::CornerBlock(QGameItem * parent,CornerType::Type type)
    : Block(parent)
{
    corner_type = type;
    block_type = BlockType::CORNER;
    effect_player = new QMediaPlayer();
}

CornerBlock::~CornerBlock()
{
    delete effect_player;
}


// Methods
void CornerBlock::enter(Player* player)
{
    qDebug() << "In corner block " << corner_type;
    using namespace CornerType;
    switch(corner_type) {
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

//when arrived at dormitory block, give oppertunity to learn one subject again
void CornerBlock::inDormitory(Player* player) 
{
    using namespace CharacterType;
    QMessageBox warn_box;
    warn_box.setStandardButtons(QMessageBox::Ok);
    warn_box.setDefaultButton(QMessageBox::Ok);

    player->giveSalary();

    std::list<Block*> block_list = player->getBlocks();
    if(block_list.size() > 0) {

        warn_box.setText("재수강할 과목을 선택해주세요.");
        warn_box.exec();
        LocalGame::getInst()->setGameState(LocalGameState::CORNER_RETAKE_SUBJECT);
    }
    else {
        warn_box.setText("재수강할 과목이 없네요. 공부좀 하세요.");
        warn_box.exec();
        LocalGame::getInst()->turnOver();
    }
}

//when arrived at 61call block, give oppertunity to move other block which you want to move (p=1/4)
void CornerBlock::in61Call(Player* player)
{
    QMessageBox warn_box;
    warn_box.setStandardButtons(QMessageBox::Ok);
    warn_box.setDefaultButton(QMessageBox::Ok);
    if((rand() % 1)==0)
    {
        // play 61call sound
        effect_player->setMedia(QUrl::fromLocalFile(QFileInfo("sound/61call.wav").absoluteFilePath()));
        effect_player->play();

        warn_box.setText("61콜 택시 성공! 이동하고 싶은 블럭을 선택하세요!");
        warn_box.exec();
        LocalGame::getInst()->setGameState(LocalGameState::JUMP_PLAYER);
    }

    else
    {
        warn_box.setText("61콜 택시 실패! 다음 기회에...");
        warn_box.exec();
        LocalGame::getInst()->turnOver();
    }

}

//in breaksemester, rest 3 turns. If dice were double at rest, you would be able to escape..
void CornerBlock::inBreakSemester(Player* player)
{
    QMessageBox warn_box;
    warn_box.setStandardButtons(QMessageBox::Ok);
    warn_box.setDefaultButton(QMessageBox::Ok);

    warn_box.setText("휴학! 2턴동안 쉽니다.");
    warn_box.exec();
    // play 61call sound
    effect_player->setMedia(QUrl::fromLocalFile(QFileInfo("sound/no.wav").absoluteFilePath()));
    effect_player->play();

    //LocalGame에서 모두 구현되어 있음
    player->setMouindo(2);
    LocalGame::getInst()->turnOver();

    //1.원래 무인도에 있다가 다시 턴이 된 경우 -> 주사위를 굴릴 수 있게 한다.
    //2.다른 칸에 있다가 갑자기 무인도에 온 경우->바로 쉬게 한다.
    //3.휴식 횟수 새는 기능.
}

//in pluralmajor block, stochastically you should monopolize 2 department (odds=1/6)
void CornerBlock::inPluralMajor(Player* player)
{
    QMessageBox warn_box;
    if(player->isPlural())
    {
        warn_box.setStandardButtons(QMessageBox::Ok);
        warn_box.setDefaultButton(QMessageBox::Ok);
        warn_box.setText(QString("주변의 만류로 인해 복수전공을 안하기로 결정했습니다."));
        warn_box.exec();
    }
    else{
        switch((rand() % 6)==1) {
            case 1:
                qDebug() <<"You have to take plural major.";

                warn_box.setStandardButtons(QMessageBox::Ok);
                warn_box.setDefaultButton(QMessageBox::Ok);
                warn_box.setText(QString("복수전공 결심! 승리하려면 두 가지 전공을 이수해야 합니다."));
                warn_box.exec();

                // play no! sound
                effect_player->setMedia(QUrl::fromLocalFile(QFileInfo("sound/no.wav").absoluteFilePath()));
                effect_player->play();

                player->setPlural(true);
                break;

            default:
                warn_box.setStandardButtons(QMessageBox::Ok);
                warn_box.setDefaultButton(QMessageBox::Ok);
                warn_box.setText(QString("복수전공은 하지 않기로 했습니다."));
                warn_box.exec();
                qDebug()<<"You don't have to take plural major.";
        }
    }
    //학과 1개 독점 시에 복수전공 해제& 두개 독점 시에 승리 그리고 만약에 한개 독점 하고 두개째 도전중일 때다른 누군가가 독점된 학과를 뺏어가는 경우!?

    LocalGame::getInst()->turnOver();
}
