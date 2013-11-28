#include "player.h"
#include "subjectblock.h"
#include "types.h"
#include <iostream>
#include <algorithm>
#include <QDebug>

using namespace std;

Player::Player()
{
    position = 0;
    energy = 0;
    bankrupt = false;
    mobile = true;
    panelty = 0;
    plural = false;
    character_type = CharacterType::NONE;

    //initialize map
    using namespace SubjectType;
    registered[BIO] = 0;
    registered[CHEM] = 0;
    registered[CSE] = 0;
    registered[EE] = 0;
    registered[MATH] = 0;
    registered[ME] = 0;
    registered[MSE] = 0;
    registered[PHYS] = 0;

    // end initialize
    qDebug() << "Player Created" << endl;
}


Player::~Player()
{
   //delete own_blocks;

    qDebug() << "Player Destroyed" << endl;
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


CharacterType::Type Player::getType() const
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
    int moveValue = position + dice;

    // pay check
    if(moveValue >= 32) {
        giveSalary();
        moveValue %= 32;
    }

    setPosition(moveValue);

    // some character animations
}


// check whether player has block or not
bool Player::hasBlock(Block* block)
{
    list<Block*>::iterator finder = own_blocks.end();
    finder = find(own_blocks.begin(), own_blocks.end(), block);

    // no matching
    if(finder == own_blocks.end())
        return false;

    // match found
    else
        return true;
}


//
void Player::buyBlock(Block* block)
{
    takeBlock(block);
    //energy -= block->getValue();

}


void Player::sellBlock(Block* block)
{
    loseBlock(block);
    //energy += block->getValue();
}


void Player::takeBlock(Block *block)
{
    using namespace BlockType;

    // exception handling
    if(block->getType() != SUBJECT) {
        qDebug() << "Block is not subject block." << endl;
        return;
    }

    if(!hasBlock(block)) {
        qDebug() << "You don't have that block. Check Again!" << endl;
        return;
    }

    // do some operations
    registered.find(((SubjectBlock*)block)->getType())->second++;
    own_blocks.push_back(block);
}


void Player::loseBlock(Block *block)
{
    using namespace BlockType;

    // exception handling
    if(block->getType() != SUBJECT) {
        qDebug() << "Block is not subject block." << endl;
        return;
    }

    if(!hasBlock(block)) {
        qDebug() << "You don't have that block. Check Again!" << endl;
        return;
    }

    // do some operations
    registered.find(((SubjectBlock*)block)->getType())->second--;
    own_blocks.remove(block);
}


void Player::giveSalary()
{
    if(character_type == CharacterType::HARD_WORKER)
    	energy += 150;
    else
    	energy += 100;
}


bool Player::checkWinStatus()
{
    int majored = 0;

    // iterate map to check completed majors
    for(map<SubjectType::Type, int>::iterator i = registered.begin(); i != registered.end(); i++) {
        if(i->second == 3)
            majored ++;
    }

    // plural major & passed
    if(plural && majored >= 2)
        return true;

    // single major & passed
    else if (!plural && majored >= 1)
        return true;

    // still playing
    else
        return false;
}


void Player::payEnergy(int payenergy)
{
    energy-=payenergy;
}


void Player::takeEnergy(int paidenergy){
    energy+=paidenergy;
}


