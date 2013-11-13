#include<time.h>
#include<stdlib.h>


class Dice
{
protected:
	int value1;
	int value2;
public:
void roll();
bool isDouble();
int getSum();
};

void Dice::roll()
{
	srand((unsigned)time(NULL)+rand());
	value1=rand()%6+1;
	srand((unsigned)time(NULL)+rand()); 
	value2=rand()%6+1;
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
