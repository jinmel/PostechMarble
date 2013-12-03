#include <QDebug>
#include <iostream>
#include "block.h"
#include "cornerblock.h"
#include "player.h"
#include "dice.h"
#include "localgame.h"

using namespace std;

CornerBlock::CornerBlock(QGameItem * parent,CornerType::Type type)
    : Block(parent)
{
    corner_type = type;
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
    LocalGame::getInst()->turnOver();
}

void CornerBlock::inDormitory(Player* player)
{
    using namespace CharacterType;

    int takingenergy;
    switch(player->getType())
    {
    case LOL :
        takingenergy = 100; //주는 에너지 수치는 상학선배&주현이가 채워주세요 ㅎㅎ
        break;

    case GENIUS :
        takingenergy = 100;
        break;

    case HARD_WORKER :
        takingenergy = 150;
        break;

    case OUTSIDER :
        takingenergy = 100;
        break;

    case ALCOHOLIC :
        takingenergy = 100;
        break;
    default :
        takingenergy = 100;
    }
    player->setEnergy(player->getEnergy() + takingenergy);

}


void CornerBlock::in61Call(Player* player)
{
    if((rand() % 6)==0)
    {
        qDebug() << "in 61Call";
        qDebug() <<"You can choose any block.";
        //player->walkBy(blocknum);//moveTo에서 포인터가지고 어찌어찌해서 옮겨줘야될꺼같은데!!
    }
    /*moveTo 를 숫자로 넣을수 있도록 해야할듯!! 현재 있는 칸도 번호 저장해둬서 주사위 돌렸을 때 현재 숫자+주사위 눈 으로 이동하든지
    이런 경우에 바로 숫자 입력해서 이동할 수 있도록 하든지*/
    //--------->ok!
    else
    {
        qDebug() <<"You failed to take 61 call taxi.";
    }

}

void CornerBlock::inBreakSemester(Player* player)
{
    qDebug() << "in BreakSem";

    if(player->getPenalty()==0)//다른 블럭에서 들어왔을 경우
    {
        qDebug()<< "You have to break the 3 semesters in this block.";
        player->setMouindo(3);
    }
    else//원래 이 블럭에 있었을 경우.. 근데 enter라는 함수로 해결이 되는가?
    {
        if(player->getEnergy()>=200)
        {
            qDebug()<<"You can escape the mouindo if you pay energy or get a double dice";
            qDebug()<<"1. pay energy    2. roll a dice"<<endl;//나중에 애니메이션 넣어서 바꿀 부분
            int userselect;
            cin>>userselect;
            if(userselect==1 && player->getEnergy()>=200)
            {
                player->payEnergy(200);

                while(player->getPenalty() >=0)//panelty 없애주고
                {
                 player->escapeMouindo();
                }
                qDebug()<<"Rolling a dice to go another block.";
                Dice::getInst()->roll();
                player->walkBy(Dice::getInst()->getValue());
            }
            else if(userselect==2)
            {
                Dice::getInst()->roll();
                if(Dice::getInst()->isDouble())
                {
                    while(player->getPenalty() >=0)
                    {
                        player->escapeMouindo();
                    }
                    qDebug()<<"Rolling a dice to go another block.";
                    Dice::getInst()->roll();
                    player->walkBy(Dice::getInst()->getValue());
                }
                else//not double
                {
                    player->escapeMouindo();//(panelty 1개 감소)
                }
            }
            else
            qDebug()<<"wrong input";
        }
        else //행동력이 200보다 적은 경우 묻지 않고 자동으로 더블 확인
        {
                Dice::getInst()->roll();
                if(Dice::getInst()->isDouble())
                {
                    while(player->getPenalty() >=0)
                    {
                        player->escapeMouindo();
                    }
                    qDebug()<<"Rolling a dice to go another block.";
                    Dice::getInst()->roll();
                    player->walkBy(Dice::getInst()->getValue());
                }
                else//not double
                {
                    player->escapeMouindo();//(panelty 1개 감소)
                }
        }
    }
    //아... 무인도에 갇힌 횟수 !!!!***********구현해야즤

    //1.원래 무인도에 있다가 다시 턴이 된 경우 -> 주사위를 굴릴 수 있게 한다.
    //2.다른 칸에 있다가 갑자기 무인도에 온 경우->바로 쉬게 한다.
    //3.휴식 횟수 새는 기능.
    //돈을 낼 수 있는지 없는지도 검사해야하는 것 아닙니까
}

void CornerBlock::inPluralMajor(Player* player)
{
    qDebug() << "You have to take two major for graduation.";
    qDebug() << "Plural major check...";

    switch((rand()%6)==1) {
        case 1: qDebug() <<"You have to take plural major.";
            player->setPlural(true);
            break;

        default: qDebug()<<"You don't have to take plural major.";

    }//학과 1개 독점 시에 복수전공 해제& 두개 독점 시에 승리 그리고 만약에 한개 독점 하고 두개째 도전중일 때다른 누군가가 독점된 학과를 뺏어가는 경우!?
}
