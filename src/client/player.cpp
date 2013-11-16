#include "player.h"
#include <iostream>

using namespace std;


Player::Player()
{
	cout << "Player Created" << endl;
    energy = 0;
    position = 0;
    bankrupt = false;
    mobile = true;
    character_type = NONE;
	checkmouindo = 0;
	checkwinstatus = false;
}


Player::~Player()
{
	cout << "Player Destroyed" << endl;
}


// Accessor Methods
int Player::getPosition() const
{
    return position;
}


bool Player::isMobile() const
{
    return mobile;
}


int Player::getEnergy() const
{
    return energy;
}

CharacterType Player::getCharacter_Type()  const
{
	return character_type;
}

int Player::getMouindo() const
{
	return checkmouindo;
}


// Methods
void Player::setPosition(int position)
{
    this->position = position;
}
void Player::setEnergy(int getenergy){
	energy = getenergy;
}

void Player::moveTo(int position)
{
	setPosition(position);

    // some character animations
	//해당하는 블럭에 player 포인터를 저장하게 해서현재 그 블럭위에있는 player를 나타내는건..?

}


bool Player::checkWinStatus()
{
	return checkwinstatus;
}


int Player::checkMouindo()
{
    return checkmouindo;
}
void Player::setMouindo(int mouindonumber)
{
	checkmouindo = mouindonumber;
}

bool Player::escapeMouindo()
{
    return false;
}

