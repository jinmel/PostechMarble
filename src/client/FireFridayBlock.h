#progma once
#include "block.h"


class FireFridayBlock
{
public:
    enum FireFridayType {
        TWODARI,SEOULJONGBIN,TONGZIP,CHAMPYO
    };

private:
    FireFridayType block_type;

public:
    FireFridayBlock();
    virtual ~FireFridayBlock();
    void inFireFridayBlock(Player* player);//in Cornerblock, execute this function
                        //This function : type check and call correct function
    void inTWODARI(Player* player);
    void inSEOULJONGBIN(Player* player);
    void inTONGZIP(Player* player);
    void inCHAMPYO(Player* player);


};
