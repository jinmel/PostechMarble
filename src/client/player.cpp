#include "player.h"
#include <iostream>
#include <algorithm>

using namespace std;

Player::Player()
{
    position = 0;
    energy = 0;
    bankrupt = false;
    mobile = true;
    panelty = 0;
    own_blocks = new list<Block*>;
    character_type = NONE;

    cout << "Player Created" << endl;
}


Player::~Player()
{
    delete own_blocks;

    cout << "Player Destroyed" << endl;
}


// Accessor Methods
int Player::getPosition() const
{
    return position;
}


bool Player::isBankrupt() const
{
    return bankrupt;
}


bool Player::isMobile() const
{
    return mobile;
}


int Player::getEnergy() const
{
    return energy;
}


int Player::getPanelty() const
{
    return panelty;
}


CharacterType Player::getCharactorType()  const
{
	return character_type;
}


// Methods
void Player::setPosition(int position)
{
    this->position = position;
}


void Player::setEnergy(int energy){
    this->energy = energy;
}


// set player to stay mouindo
// parm: how long to stay in mouindo
void Player::setMouindo(int panelty)
{
    this->panelty = panelty;
    mobile = false;
}


// check player escaped or not
bool Player::escapeMouindo()
{
    if(mobile)
        return true;

    else {

        if(panelty == 0) {
            mobile = true;
            return true;
        }

        else {
            // roll a dice
            panelty--;
            return false;

        }
    }
}


void Player::moveTo(int dice)
{
    setPosition(position + dice);

    // some character animations
    // 해당하는 블럭에 player 포인터를 저장하게 해서현재 그 블럭위에있는 player를 나타내는건..?

}


bool Player::hasBlock(Block* block)
{
    own_blocks::iterator finder = own_blocks.end();
    finder = find(own_blocks.begin(), own_blocks.end(), block);

    // no matching
    if(finder == own_blocks.end())
        return false;
    else
        return true;
}


void Player::buyBlock(Block* block)
{
    own_blocks.push_back(block);
}


void Player::sellBlock(Block* block)
{
    own_blocks.remove(block);
}


bool Player::checkWinStatus()
{
    // some check method
    return false;      // this is dummy
}
