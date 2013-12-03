#pragma once
#include <QObject>

class Dice;

class Dice : public QObject
{
    Q_OBJECT
private:
	Dice();
	static Dice* m_inst;
	int value1;
	int value2;
public:
	~Dice();
	void roll();
    int getFirstDice();
    int getSecondDice();
	bool isDouble();
    int getValue();

	// Static Methods
	static Dice* getInst();
	static void delInst();
signals:
    void firstDiceRolled(int value);
    void secondDiceRolled(int value);
    void diceRolled(int value,bool is_double);
    void diceRolled(int value);
    void diceRolled(Dice *dice);
};


