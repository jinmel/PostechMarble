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
    blocks = new Block*[32];


    blocks[0] = new CornerBlock;

    blocks[1] = new SubjectBlock;
    blocks[2] = new SubjectBlock;
    blocks[3] = new SubjectBlock;


    blocks[4] = new SubjectBlock;

    blocks[5] = new FireFridayBlock;

    blocks[6] = new SubjectBlock;
    blocks[7] = new SubjectBlock;

    blocks[8] = new CornerBlock;
    
    blocks[9] = new SubjectBlock;

    blocks[10] = new SubjectBlock;
    blocks[11] = new SubjectBlock;
    blocks[12] = new EventBlock;

    blocks[13] = new SubjectBlock;
    
    blocks[14] = new SubjectBlock;
    blocks[15] = new SubjectBlock;
    blocks[16] = new CornerBlock;
    
    blocks[17] = new SubjectBlock;

    blocks[18] = new SubjectBlock;
    
    blocks[19] = new SubjectBlock;
    blocks[20] = new SubjectBlock;
    blocks[21] = new SubjectBlock;

    blocks[22] = new SubjectBlock;

    blocks[23] = new FireFridayBlock;
    blocks[24] = new CornerBlock;
    blocks[25] = new SubjectBlock;
    
    blocks[26] = new SubjectBlock;

    blocks[27] = new SubjectBlock;
    
    blocks[28] = new EventBlock;

    blocks[29] = new SubjectBlock;
    blocks[30] = new SubjectBlock;
    blocks[31] = new SubjectBlock;
    
    for(int i=0; i<32; i++) {
        blocks[i]->setPosition(i);
    }

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

