#include "dice.h"

Dice::Dice()
{
	srand((unsigned)time(NULL));
}

void Dice::roll()
{
	value1 = rand()%6+1;
	value2 = rand()%6+1;
}

bool Dice::isDouble()
{
	if(value1==value2)
		return true;

	if(value1!=value2)
		return false;
}

int Dice::getSum()
{
	return value1+value2;
}