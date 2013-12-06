#include <iostream>
#include "block.h"
#include "firefridayblock.h"
#include "player.h"
#include "dice.h"
#include "sellpopup.h"
#include "localgame.h"
#include "types.h"
// Constructor & Destructor
FireFridayBlock::FireFridayBlock(QGameItem * parent,FireFridayType::Type type)
    : Block(parent)
{
    firefriday_type = type;
    block_type = BlockType::FRIDAY;
}

FireFridayBlock::~FireFridayBlock()
{

}


// Methods
void FireFridayBlock::enter(Player *player) // player enter firefriday block
{
    using namespace FireFridayType;

    switch(firefriday_type)
    {
        case SEOULJONGBIN: inSEOULJONGBIN(player); // seouljongro
            break;
        case TONGZIP: inTONGZIP(player);            //Tong zip
            break;
    }
    LocalGame::getInst()->turnOver();
}

void FireFridayBlock::inSEOULJONGBIN(Player *player) 
{
    if(player->getType()!=CharacterType::ALCOHOLIC) // if you are not alchoholic 
    {
        if(player->getEnergy() >= 100)
            player->payEnergy(100);
        else
            player->setEnergy(0);
    }
    else
    {
        player->giveEnergy(100);
    }
}

void FireFridayBlock::inTONGZIP(Player *player)         // Tongzip same with seouljongro
{
    if(player->getType()!=CharacterType::ALCOHOLIC)
    {
        if(player->getEnergy() >= 100)
            player->payEnergy(100);
        else
            player->setEnergy(0);
    }
    else
    {
        player->giveEnergy(100);
    }
}
