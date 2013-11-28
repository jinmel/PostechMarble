#include <QDebug>
#include <iostream>
#include "block.h"
#include "cornerblock.h"
#include "player.h"
#include "dice.h"

using namespace std;

CornerBlock::CornerBlock()
{
}


CornerBlock::~CornerBlock()
{
}


// Methods
void CornerBlock::enter(Player* player)
{
	inCornerBlock(player);
}


void CornerBlock::inCornerBlock(Player* player)
{
    using namespace CornerType;

    switch(block_type)
    {
        case DORMITORY : inDormitory(player);
            break;
        case THE61CALL : in61Call(player);
            break;
        case BREAKSEMESTER : inBreakSemester(player);
            break;
        case PLURALMAJOR : inPluralMajor(player);
            break;
        default : qDebug()<<"CornerBlock error!"<<endl;
            break;
    }
}

void CornerBlock::inDormitory(Player* player)
{
    using namespace CharacterType;

    int takingenergy;
    switch(player->getType())
    {
        case LOL : takingenergy = 100; //주는 에너지 수치는 상학선배&주현이가 채워주세요 ㅎㅎ
            break;

        case GENIUS : takingenergy = 100;
            break;

        case HARD_WORKER : takingenergy = 150;
            break;

        case OUTSIDER : takingenergy = 100;
            break;

        case ALCOHOLIC : takingenergy = 100;
            break;

        default         : takingenergy = 100;

    }

    player->setEnergy(player->getEnergy() + takingenergy);

}


void CornerBlock::in61Call(Player* player) {        //원하는 블럭을 선택할 수 있게 함

    qDebug() <<"You can choose any block."<< endl;
    qDebug() <<">>";
    int blocknum;//0~35까지의 숫자로 block 번호 관리... 이렇게 안하면 board 어레이로 올라가야하는데.. 뭐 할라면 할순잇겟지..
    cin >> blocknum; //ui는 블럭을 클릭 할 수 있도록, 우리는 클릭받은 블럭의 입력받아서 여기에 cin대신에 넣을 수 있어야겠지.. clicked()이용해야할듯 ㅎ
    qDebug() <<" "<<endl;
    player->moveTo(blocknum);//moveTo에서 포인터가지고 어찌어찌해서 옮겨줘야될꺼같은데!! 


    /*moveTo 를 숫자로 넣을수 있도록 해야할듯!! 현재 있는 칸도 번호 저장해둬서 주사위 돌렸을 때 현재 숫자+주사위 눈 으로 이동하든지
    이런 경우에 바로 숫자 입력해서 이동할 수 있도록 하든지*/
    //--------->ok!

}
void CornerBlock::inBreakSemester(Player* player) {     //무인도

    if(player->getPanelty()==0)//다른 블럭에서 들어왔을 경우
    {
        qDebug()<<"You have to break the 3 semesters in this block."<<endl;
        player->setMouindo(3);
    }
    else//원래 이 블럭에 있었을 경우.. 근데 enter라는 함수로 해결이 되는가?
    {

        qDebug()<<"You can escape the mouindo if you pay energy or get a double dice"<<endl;
        qDebug()<<"1. pay energy    2. roll a dice"<<endl;//나중에 애니메이션 넣어서 바꿀 부분
        qDebug()<<">>";
        int userselect;
        cin>>userselect;
        if(userselect==1)
        {
            player->payEnergy(1/*내야하는 벌금만큼*/);

            while(player->getPanelty() >=0)//panelty 없애주고
            {
                player->escapeMouindo();
            }
            qDebug()<<"Rolling a dice to go another block."<<endl;
            Dice::getInst()->roll();
            player->moveTo(Dice::getInst()->getValue());


        }
        else if(userselect==2)
        {
            Dice::getInst()->roll();
            if(Dice::getInst()->isDouble())
            {
                while(player->getPanelty() >=0)
                {
                    player->escapeMouindo();
                }
                qDebug()<<"Rolling a dice to go another block."<<endl;
                Dice::getInst()->roll();
                player->moveTo(Dice::getInst()->getValue());

            }
            else//not double
            {
                player->escapeMouindo();//(panelty 1개 감소)
            }

        }
        else
            qDebug()<<"wrong input"<<endl;

    }
    //아... 무인도에 갇힌 횟수 !!!!***********구현해야즤

    //1.원래 무인도에 있다가 다시 턴이 된 경우 -> 주사위를 굴릴 수 있게 한다.
    //2.다른 칸에 있다가 갑자기 무인도에 온 경우->바로 쉬게 한다.
    //3.휴식 횟수 새는 기능.

}

void CornerBlock::inPluralMajor(Player* player) {//복수전공


    qDebug()<<"You have to take two major for graduation."<<endl;
    qDebug()<<"Plural major check..."<<endl;
<<<<<<< HEAD

    Dice::getInst()->roll();


    int checkplural=Dice::getInst()->getValue();//1=plural 2,3,4,5,6=normal
    switch(checkplural)
    {
    case 1 : qDebug() <<"You have to take plural major."<<endl;
=======
	
	Dice::getInst()->roll();
	

    int checkplural = Dice::getInst()->getValue();      //1=plural 2,3,4,5,6=normal
	switch(checkplural)
	{
	case 1 : qDebug() <<"You have to take plural major."<<endl;
>>>>>>> 700b751d317078be635f452f03b1aeb0da89d4e8
        player->setPlural(true);
        break;
    default : qDebug()<<"You don't have to take plural major."<<endl;

    }//학과 1개 독점 시에 복수전공 해제& 두개 독점 시에 승리 그리고 만약에 한개 독점 하고 두개째 도전중일 때다른 누군가가 독점된 학과를 뺏어가는 경우!?
}
