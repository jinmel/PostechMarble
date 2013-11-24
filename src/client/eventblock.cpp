#include "eventblock.h"
#include <ctime>
#include <iostream>
#include <cstdlib>

using namespace std;

// Constructor & Destructor
EventBlock::EventBlock(int position)
{
    this->position = position;
}


EventBlock::~EventBlock()
{
}


// Methods
void EventBlock::enter(Player* player)
{

}


void EventBlock::checkEvent(Player* player)
{
	// 이벤트 블럭을 밟을시 실행하여 랜덤한 이벤트 발생
	srand((unsigned)time(NULL));
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
		clubActivity(player);
		break;
	}
}

void EventBlock::drink(Player* player)
{
	// 음주로 인한 행동력 감소
	player->setEnergy(player->getEnergy() - 100);
}

void EventBlock::cc(Player* player)
{
	// 커플 활동으로 인한 행동력 감소 ( 아니면 일정 확률로 오르게? )
	player->setEnergy(player->getEnergy() - 100);
}

void EventBlock::takeSubject(Player* player)
{
	// 플레이어가 과목을 하나 선택한 후 buyBlock을 실행한다
    //player->buyBlock();
}

void EventBlock::loseSubject(Player* player)
{
	// 플레이어가 과목 하나를 잃는다. (랜덤 or 선택)
    //player->sellBlock();
}

void EventBlock::lol(Player* player)
{
	// 롤 너무 많이해서 행동력 대폭 감소
	player->setEnergy(player->getEnergy() - 100);
}

void EventBlock::eatChicken(Player* player)
{
	// 치느님을 영접하여 행동력 증가
	player->setEnergy(player->getEnergy() + 100);

}

void EventBlock::clubActivity(Player* player)
{
	// 동아리 활동으로 공부할 시간이 없다.
	player->setEnergy(player->getEnergy() - 100);
}
