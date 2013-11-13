#pragma once

#include<ctime>
#include<cstdlib>

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


