#include "player.h"
#include "subjectblock.h"
#include "types.h"
#include <iostream>
#include <algorithm>
#include <QDebug>
#include <QtGlobal>

using namespace std;

Player::Player(QGameItem* parent,int _id) : QGameItem(parent)
{
    id = _id;
    name = "";
    position = 0;
    energy = 0;
    bankrupt = false;
    mobile = true;
    penalty = 0;
    plural = false;
    character_type = CharacterType::NONE;
    totalownsubjectenergy=0;

    //initialize map
    using namespace SubjectType;
    registered[BIO] = 0;
    registered[CHEM] = 0;
    registered[CSED] = 0;
    registered[EE] = 0;
    registered[MATH] = 0;
    registered[ME] = 0;
    registered[IME] = 0;
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


int Player::getPenalty() const
{
    return penalty;
}

bool Player::isPlural() const
{
    return plural;
}


CharacterType::Type Player::getType() const
{
    return character_type;
}


Block** Player::getBlocks() const
{
    Block** blocks = new Block*[own_blocks.size()];

    for (int i=0; i< own_blocks.size(); i++)
        blocks[i] = own_blocks[i];

    return blocks;
}


int Player::getTotalOwnSubjectEnergy() const
{
    return totalownsubjectenergy;
}

// Methods
void Player::setEnergy(int energy)
{
    this->energy = energy;
}


void Player::setPlural(bool plural)
{
    this->plural = plural;
}


void Player::addTotalOwnSubjectEnergy(int subjectenergy){
    this->totalownsubjectenergy+=subjectenergy;

    }
void Player::setBankrupt(bool bankrupt)
{
    this->bankrupt=bankrupt;
}

void Player::pushBlock(Block* block)
{
    own_blocks.push_back(block);

}
// set player to stay mouindo
// parm: how long to stay in mouindo
void Player::setMouindo(int panelty)
{
    this->penalty = panelty;
    mobile = false;
}


// check player escaped or not
bool Player::escapeMouindo()
{
    if(mobile)
        return true;

    else {

        if(penalty == 0) {
            mobile = true;
            return true;
        }

        else {
            // roll a dice
            penalty--;
            return false;

        }
    }
}


void Player::walkTo(int dice)
{
    Q_ASSERT(dice <= 12 && dice >=2);
    int currentpos = position;
    int next_pos = position + dice;
    if(next_pos >= 36) {
        giveSalary();
        next_pos %= 36;
    }

    jumpTo(next_pos);
}

void Player::jumpTo(int block_num){
    this->position = block_num;

    // some kind of animation?: NO
    //this->setPos(getCoord());
}

void Player::removeBlock(Block* block){
    own_blocks.remove(block);
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
    using namespace BlockType;

    if(!hasBlock(block))
        qDebug() << "You don't have that block. Check Again!" << endl;

    else {
        switch(block->getType()) {
        case CORNER:
            // CornerBlock
            break;
        case EVENT:
            // EventBlock
            break;
        case FRIDAY:
            // FriayBlock
            break;
        case SUBJECT:
            // SubjectBlock
            registered.find(((SubjectBlock*)block)->getType())->second++;
            totalownsubjectenergy+=block->getValue();
            break;
        }

        own_blocks.push_back(block);
    }

    energy -= block->getValue();

}


void Player::sellBlock(Block* block)
{
    using namespace BlockType;

    if(!hasBlock(block))
        qDebug() << "You don't have that block. Check Again!" << endl;

    else {
        switch(block->getType()) {
        case CORNER:
            // CornerBlock
            break;
        case EVENT:
            // EventBlock
            break;
        case FRIDAY:
            // FriayBlock
            break;
        case SUBJECT:
            // SubjectBlock
            registered.find(((SubjectBlock*)block)->getType())->second--;
            totalownsubjectenergy-=block->getValue();
            break;

        }

        own_blocks.remove(block);
    }
    energy += block->getValue();
}


void Player::takeBlock(Block *block)
{
    using namespace BlockType;

    if(!hasBlock(block))
        qDebug() << "You don't have that block. Check Again!" << endl;

    else {
        switch(block->getType()) {
        case CORNER:
            // CornerBlock
            break;
        case EVENT:
            // EventBlock
            break;
        case FRIDAY:
            // FriayBlock
            break;
        case SUBJECT:
            // SubjectBlock
            registered.find(((SubjectBlock*)block)->getType())->second++;
            totalownsubjectenergy+=block->getValue();
            break;
        }

        own_blocks.push_back(block);
    }
}


void Player::loseBlock(Block *block)
{
    using namespace BlockType;

    if(!hasBlock(block))
        qDebug() << "You don't have that block. Check Again!" << endl;

    else {
        switch(block->getType()) {
        case CORNER:
            // CornerBlock
            break;
        case EVENT:
            // EventBlock
            break;
        case FRIDAY:
            // FriayBlock
            break;
        case SUBJECT:
            // SubjectBlock
            registered.find(((SubjectBlock*)block)->getType())->second--;
            totalownsubjectenergy-=block->getValue();
            break;

        }

        own_blocks.remove(block);
    }
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

    for(map<SubjectType::Type, int>::iterator i = registered.begin(); i != registered.end(); i++) {
        if(i->second == 3)
            majored ++;
    }

    if(plural && majored >= 2)
        return true;
    else if (!plural && majored >= 1)
        return true;
    else
        return false;
}

void Player::payEnergy(int payenergy)
{
    energy-=payenergy;

}
void Player::paidEnergy(int paidenergy){
    energy+=paidenergy;

}

int Player::getId() const {
    return id;
}

void Player::setType(CharacterType::Type type) {
    character_type = type;
}

