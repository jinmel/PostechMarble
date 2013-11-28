#include <iostream>
#include "block.h"
#include "firefridayblock.h"
#include "player.h"
#include "dice.h"

FireFridayBlock::FireFridayBlock(Type type)
{
    block_type = type;
}

FireFridayBlock::~FireFridayBlock()
{

}

void FireFridayBlock::enter(Player *player)
{
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
    if(getType()!=SEOULJONGBIN)
    player->setEnergy(player->getEnergy() - 100);
}

void FireFridayBlock::inTONGZIP(Player *player)
{
    if(getType()!=TONGZIP)
    player->setEnergy(player->getEnergy() - 100);
}
