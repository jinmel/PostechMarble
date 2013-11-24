#include <iostream>
#include "block.h"
#include "firefridayblock.h"
#include "player.h"
#include "dice.h"


FireFridayBlock::FireFridayBlock()
{

}

FireFridayBlock::~FireFridayBlock()
{

}

void FireFridayBlock::inFireFridayBlock(Player *player)
{
    switch(block_type)
   {    case TWODARI: inTWODARI(player);
            break;
        case SEOULJONGBIN: inSEOULJONGBIN(player);
            break;
        case TONGZIP: inTONGZIP(player);
            break;
        case CHAMPYO: inCHAMPYO(player);
            break;
    }

}


void FireFridayBlock::inSEOULJONGBIN(Player *player)
{

}

void FireFridayBlock::inCHAMPYO(Player *player)
{

}

void FireFridayBlock::inTONGZIP(Player *player)
{

}

void FireFridayBlock::inTWODARI(Player *player)
{

}

