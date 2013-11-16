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


// Methods
void Player::setPosition(int position)
{
    this->position = position;
}


void Player::moveTo(int position)
{
	setPosition(position);

    // some character animations

}


bool Player::checkWinStatus()
{
	return false;
}


bool Player::checkMouindo()
{
    return false;
}


bool Player::escapeMouindo()
{
    return false;
}
