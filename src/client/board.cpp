#include <iostream>
#include "board.h"
#include "eventblock.h"
#include "subjectblock.h"
#include "cornerblock.h"
#include "firefridayblock.h"

using namespace std;

// Constructor & Destructor
Board::Board()
{
    blocks = new Block*[36];


    blocks[0] = new CornerBlock(0);

    blocks[1] = new SubjectBlock(1);
    blocks[2] = new SubjectBlock(2);
    blocks[3] = new SubjectBlock(3);


    blocks[4] = new SubjectBlock(4);

    blocks[5] = new FireFridayBlock(5);

    blocks[6] = new SubjectBlock(5);
    blocks[7] = new SubjectBlock(6);

    blocks[8] = new EventBlock(7);
    
    blocks[9] = new CornerBlock(8);

    blocks[10] = new SubjectBlock(0);
    blocks[11] = new SubjectBlock(0);
    blocks[12] = new SubjectBlock(0);

    blocks[13] = new EventBlock(0);
    
    blocks[14] = new SubjectBlock(0);
    blocks[15] = new SubjectBlock(0);
    blocks[16] = new SubjectBlock(0);
    
    blocks[17] = new FireFridayBlock(17);

    blocks[18] = new CornerBlock(0);
    
    blocks[19] = new SubjectBlock(0);
    blocks[20] = new SubjectBlock(0);
    blocks[21] = new SubjectBlock(0);

    blocks[22] = new EventBlock(0);

    blocks[23] = new SubjectBlock(0);
    blocks[24] = new SubjectBlock(0);
    blocks[25] = new SubjectBlock(0);
    
    boards[26] = new FireFridayBlock(26);

    blocks[27] = new CornerBlock(0);
    
    boards[28] = new FireFridayBlock(28);

    blocks[29] = new SubjectBlock(0);
    blocks[30] = new SubjectBlock(0);
    blocks[31] = new SubjectBlock(0);
    
    blocks[32] = new EventBlock(0);

    blocks[33] = new SubjectBlock(0);
    blocks[34] = new SubjectBlock(0);
    blocks[35] = new SubjectBlock(0);

    cout << "Board Created" << endl;
}


Board::~Board()
{
    delete[] blocks;
}


// Methods
int Board::getLength() const
{
    return length;
}


Block* Board::getBlock(int position) const
{
    return blocks[position];
}


void Board::enter(Player* player)
{
    blocks[player->getPosition()]->enter(player);
}

