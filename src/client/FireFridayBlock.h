#pragma once
#include "block.h"
#include "types.h"


class FireFridayBlock : public Block
{
private:
    FireFridayType::Type block_type;

public:
    FireFridayBlock();
    virtual ~FireFridayBlock();
    virtual void enter(Player* player);//in Cornerblock, execute this function
                        //This function : type check and call correct function
    void inTWODARI(Player* player);
    void inSEOULJONGBIN(Player* player);
    void inTONGZIP(Player* player);
    void inCHAMPYO(Player* player);


};
