#pragma once
#include "block.h"
#include "types.h"

using namespace FireFridayType;


class FireFridayBlock : public Block
{
private:
    Type block_type;

public:
    FireFridayBlock(Type type);
    virtual ~FireFridayBlock();

    virtual void enter(Player* player);//in Cornerblock, execute this function
                        //This function : type check and call correct function
    void inSEOULJONGBIN(Player* player);
    void inTONGZIP(Player* player);

};
