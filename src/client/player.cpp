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
    plural = false;
    //own_blocks = new list<Block*>;
    character_type = NONE;

    cout << "Player Created" << endl;
}


Player::~Player()
{
   //delete own_blocks;

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

bool Player::isPlural() const
{
    return plural;
}


Player::CharacterType Player::getCharacterType() const
{
	return character_type;
}


// Methods
void Player::setPosition(int position)
{
    this->position = position;
}


void Player::setEnergy(int energy)
{
    this->energy = energy;
}


void Player::setPlural(bool plural)
{
    this->plural = plural;
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
    list<Block*>::iterator finder = own_blocks.end();
    finder = find(own_blocks.begin(), own_blocks.end(), block);

    // no matching
    if(finder == own_blocks.end())
        return false;
    else
        return true;
}


void Player::buyBlock(Block* block)
{
    if(!hasBlock(block))
        cout << "You already have that block. Check Again!" << endl;

    else {
        own_blocks.push_back(block);
        //energy -= block->getValue();
    }
}


void Player::sellBlock(Block* block)
{
    if(!hasBlock(block))
        cout << "You don't have that block. Check Again!" << endl;

    else {
        own_blocks.remove(block);
        //energy += block->getValue();
    }
}


void Player::takeBlock(Block *block)
{
    if(!hasBlock(block))
        cout << "You don't have that block. Check Again!" << endl;

    else {
        own_blocks.push_back(block);
    }
}


void Player::loseBlock(Block *block)
{
    if(!hasBlock(block))
        cout << "You don't have that block. Check Again!" << endl;

    else {
        own_blocks.remove(block);
    }
}


bool Player::checkWinStatus()
{
    // some check method
    return false;      // this is dummy
}
