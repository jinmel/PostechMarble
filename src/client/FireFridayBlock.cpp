#include <iostream>
#include "block.h"
#include "firefridayblock.h"
#include "player.h"
#include "dice.h"


FireFridayBlock::FireFridayBlock(FireFridayType type)
{
    block_type = type;
}

FireFridayBlock::~FireFridayBlock()
{

}

void FireFridayBlock::enter(Player *player)
{
    using namespace FireFridayType;

    switch(block_type)
   {    
        case SEOULJONGBIN: inSEOULJONGBIN(player);
            break;
        case TONGZIP: inTONGZIP(player);
            break;
    }

}


void FireFridayBlock::inSEOULJONGBIN(Player *player)
{
    if(getType()!=ALCOHOLIC)
    player->setEnergy(player->getEnergy() - 100);
}

void FireFridayBlock::inTONGZIP(Player *player)
{
    if(getType()!=ALCOHOLIC)
    player->setEnergy(player->getEnergy() - 100);
}
