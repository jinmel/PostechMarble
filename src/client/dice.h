#pragma once

class Dice
{
private:
	Dice();
	static Dice* m_inst;
	int value1;
	int value2;

public:
	~Dice();
	void roll();
	bool isDouble();
	int getSum();

	// Static Methods
	static Dice* getInst();
	static void delInst();
};


