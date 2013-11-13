#include "player.h"

Player::Player()
{
    energy = 0;
    position = 0;
    bankrupt = false;
    mobile = true;
    character_type = NONE;
}


Player::~Player()
{

}


// Accessor Methods
int Player::getPosition()
{
    return position;
}


bool isMobile()
{
    return mobile;
}




// Methods
void Player::setPosition(int position)
{
    this->position = position;
}


int moveTo(int position)
{

}


bool checkWinStatus()
{
	return true;
}
