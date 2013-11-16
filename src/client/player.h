#pragma once
#include <list>
#include "block.h"

class Block;
enum CharacterType {
		NONE, LOL, GENIUS, HARD_WORKER, OUTSIDER, ALCOHOLIC
	};

class Player
{
public:


private:
    int     position;
    int     energy;
    bool    bankrupt;
    bool    mobile;
    int     panelty;
	int		checkmouindo;
	bool	checkwinstatus;
    std::list<Block>   own_blocks;
    CharacterType character_type;

public:
    Player();
    ~Player();

    int getPosition() const;
    bool isMobile() const;
    int getEnergy() const;
	CharacterType getCharacter_Type() const;
	int getMouindo() const;

    void setPosition(int position);
	void setEnergy(int getenergy);
	void setMouindo(int mouindonumber);
    void moveTo(int position);//blocknumber가 position인 곳으로 이동하게 함
							//block마다 그 위에 있는 플레이어를 playerpointer(포인터 어레이 등의 방법으로?)로 저장하게 한다면 블럭으로 move할 때해당 블럭에 플레이어 포인터를 넣어줄수있겟다!? 아닌가 반대로 해야되나 뿅
    bool checkWinStatus();
    int getMouindo();//해당 player가 무인도 안에 있으면서 지난 turn.. 0이면 자유 영혼
    bool escapeMouindo();
    bool hasBlock(Block block);
    void buyBlock(Block block);
    void sellBlock(Block block);


};
      
