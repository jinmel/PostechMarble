#include "board.h"

Board::Board()
{
    boards = new Block*[36];
}


void Board::enter(Player* player)
{
	int position = player->getPosition();
    boards[position]->enter(player);
}
