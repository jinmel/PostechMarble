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


void CornerBlock::inCornerBlock(Player* player){
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
        default : cout<<"CornerBlock error!"<<endl;
            break;
    }
}

void CornerBlock::inDormitory(Player* player){

    int takingenergy;
    switch(player->getCharacterType())
    {
        case Player::LOL : takingenergy = 1; //주는 에너지 수치는 상학선배&주현이가 채워주세요 ㅎㅎ
            break;

        case Player::GENIUS : takingenergy = 2;
            break;

        case Player::HARD_WORKER : takingenergy = 3;
            break;

        case Player::OUTSIDER : takingenergy = 4;
            break;

        case Player::ALCOHOLIC : takingenergy = 5;
            break;

        default         : takingenergy = 6;

    }

    player->setEnergy(player->getEnergy() + takingenergy);

}


void CornerBlock::in61Call(Player* player) {        //원하는 블럭을 선택할 수 있게 함

    cout<<"You can choose any block."<<endl;
    cout<<">>";
    int blocknum;//0~35까지의 숫자로 block 번호 관리... 이렇게 안하면 board 어레이로 올라가야하는데.. 뭐 할라면 할순잇겟지..
    cin>> blocknum; //ui는 블럭을 클릭 할 수 있도록, 우리는 클릭받은 블럭의 입력받아서 여기에 cin대신에 넣을 수 있어야겠지..
    cout<<" "<<endl;
    player->moveTo(blocknum);//moveTo에서 포인터가지고 어찌어찌해서 옮겨줘야될꺼같은데!! 


    /*moveTo 를 숫자로 넣을수 있도록 해야할듯!! 현재 있는 칸도 번호 저장해둬서 주사위 돌렸을 때 현재 숫자+주사위 눈 으로 이동하든지
    이런 경우에 바로 숫자 입력해서 이동할 수 있도록 하든지*/
    //--------->ok!

}
void CornerBlock::inBreakSemester(Player* player) {     //무인도
    /*
     * Please Check this part
     * method name has been changed in player class
     *
    if(player->getPanelty()==0)
    {
        cout<<"You have to break the 3 semesters in this block."<<endl;
        player->setMouindo(3);
        //턴 넘어가게 하는것?!
    }

    else{
        if(player->getMouindo()==3)
    
    Dice.getInst();



    Dice.isDouble();


    }
    */


    
    //아... 무인도에 갇힌 횟수 !!!!***********구현해야즤

    //1.원래 무인도에 있다가 다시 턴이 된 경우 -> 주사위를 굴릴 수 있게 한다.
    //2.다른 칸에 있다가 갑자기 무인도에 온 경우->바로 쉬게 한다.
    //3.휴식 횟수 새는 기능.
    //dice class받을랭

}

void CornerBlock::inPluralMajor(Player* player) {//복수전공
    

	cout<<"You have to take two major for graduation."<<endl;
	cout<<"Plural major check..."<<endl;
	
	Dice::getInst()->roll();
	

	int checkplural=Dice::getInst()->getValue();//1=plural 2,3,4,5,6=normal
	switch(checkplural)
	{
	case 1 : qDebug() <<"You have to take plural major."<<endl;

	
	
	}

    //졸업 요건... 아니면 여기에 걸리면 학과독점 해도 다시 해야하는.. 장치!

}
