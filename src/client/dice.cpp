#include "dice.h"
#include <ctime>
#include <cstdlib>
#include <iostream>

using namespace std;

Dice::Dice()
{
	cout << "Dice Created" << endl;

	srand((unsigned)time(NULL));
	value1 = 0;
	value2 = 0;
}

Dice::~Dice()
{
	cout << "Dice Destroyed" << endl;
}


// Initialize Static Members
Dice* Dice::m_inst = NULL;

Dice* Dice::getInst()
{
	// create new instance if null
	if (!m_inst) {
		m_inst = new Dice();
	}

	return m_inst;
}

void Dice::delInst()
{
	// delete an instance
	if (m_inst) {
		delete m_inst;
		m_inst = NULL;
	}

	return;
}


// Methods
void Dice::roll()
{
	value1 = rand() % 6 + 1;
	value2 = rand() % 6 + 1;
}

bool Dice::isDouble()
{
	return (value1 == value2);
}

int Dice::getSum()
{
	return value1 + value2;
}