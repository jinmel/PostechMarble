#pragma once
#include "player.h"
#include "block.h"
#include <ctime>
#include <cstdlib>
#include "types.h"

class CornerBlock : public Block
{
private:
    CornerType::Type block_type;

public:
    CornerBlock(CornerType::Type type);
    virtual ~CornerBlock();

    virtual void enter(Player* player);
    void inCornerBlock(Player* player);//in Cornerblock, execute this function
                        //This function : type check and call correct function
    void inDormitory(Player* player);
    void in61Call(Player* player);
    void inBreakSemester(Player* player);
    void inPluralMajor(Player* player);
};
