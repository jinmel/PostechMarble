#include "board.h"
#include "eventblock.h"
#include "subjectblock.h"
#include "cornerblock.h"


Board::Board()
{
    boards = new Block*[36];


	boards[0] = new CornerBlock;


	static_cast<SubjectBlock*>boards[1] = new SubjectBlock;
	static_cast<SubjectBlock*>boards[2] = new SUbjectBlock;
	static_cast<SubjectBlock*>boards[3] = new SUbjectBlock;


	static_cast<SubjectBlock*>boards[4] = new SubjectBlock;
	//°ü±¤Áö
	static_cast<SubjectBlock*>boards[6] = new SubjectBlock;
	static_cast<SubjectBlock*>boards[7] = new SubjectBlock;

	boards[8] = new EventBlock;
	
	boards[9] = new CornerBlock;

	static_cast<SubjectBlock*>boards[10] = new SubjectBlock;
	static_cast<SubjectBlock*>boards[11] = new SubjectBlock;
	static_cast<SubjectBlock*>boards[12] = new SubjectBlock;

	boards[13] = new EventBlock;
	
	static_cast<SubjectBlock*>boards[14] = new SubjectBlock;
	static_cast<SubjectBlock*>boards[15] = new SubjectBlock;
	static_cast<SubjectBlock*>boards[16] = new SubjectBlock;
	
	//°ü±¤Áö

	boards[18] = new CornerBlock;
	
	static_cast<SubjectBlock*>boards[19] = new SubjectBlock;
	static_cast<SubjectBlock*>boards[20] = new SubjectBlock;
	static_cast<SubjectBlock*>boards[21] = new SubjectBlock;

	boards[22] = new EventBlock;

	static_cast<SubjectBlock*>boards[23] = new SubjectBlock;
	static_cast<SubjectBlock*>boards[24] = new SubjectBlock;
	static_cast<SubjectBlock*>boards[25] = new SubjectBlock;
	
	//°ü±¤Áö

	boards[27] = new CornerBlock;
	
	//°ü±¤Áö

	static_cast<SubjectBlock*>boards[29] = new SubjectBlock;
	static_cast<SubjectBlock*>boards[30] = new SubjectBlock;
	static_cast<SubjectBlock*>boards[31] = new SubjectBlock;
	
	boards[32] = new EventBlock;

	static_cast<SubjectBlock*>boards[33] = new SubjectBlock;
	static_cast<SubjectBlock*>boards[34] = new SubjectBlock;
	static_cast<SubjectBlock*>boards[35] = new SubjectBlock;
	

}


void Board::enter(Player* player)
{
	int position = player->getPosition();
    boards[position]->enter(player);
}
