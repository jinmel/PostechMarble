#include "board.h"
#include "eventblock.h"
#include "subjectblock.h"
#include "cornerblock.h"
#include "FireFridayBlock.h"


Board::Board()
{
    boards = new Block*[36];


	boards[0] = new CornerBlock;

	boards[1] = new SubjectBlock;
	boards[2] = new SubjectBlock;
	boards[3] = new SubjectBlock;


	boards[4] = new SubjectBlock;

    boards[5] = new FireFridayBlock;


	boards[6] = new SubjectBlock;
	boards[7] = new SubjectBlock;

	boards[8] = new EventBlock;
	
	boards[9] = new CornerBlock;

	boards[10] = new SubjectBlock;
	boards[11] = new SubjectBlock;
	boards[12] = new SubjectBlock;

	boards[13] = new EventBlock;
	
	boards[14] = new SubjectBlock;
	boards[15] = new SubjectBlock;
	boards[16] = new SubjectBlock;
	
    boards[17] = new FireFridayBlock;

	boards[18] = new CornerBlock;
	
	boards[19] = new SubjectBlock;
	boards[20] = new SubjectBlock;
	boards[21] = new SubjectBlock;

	boards[22] = new EventBlock;

	boards[23] = new SubjectBlock;
	boards[24] = new SubjectBlock;
	boards[25] = new SubjectBlock;
	
    boards[26] = new FireFridayBlock;

	boards[27] = new CornerBlock;
	
    boards[28] = new FireFridayBlock;

	boards[29] = new SubjectBlock;
	boards[30] = new SubjectBlock;
	boards[31] = new SubjectBlock;
	
	boards[32] = new EventBlock;

	boards[33] = new SubjectBlock;
	boards[34] = new SubjectBlock;
	boards[35] = new SubjectBlock;
	

}


void Board::enter(Player* player)
{
	int position = player->getPosition();
    boards[position]->enter(player);
}
