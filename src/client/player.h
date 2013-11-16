#pragma once
#include <list>
#include <block.h>

class Block;

class Player
{
public:
    enum CharacterType {
        NONE, LOL, GENIUS, HARD_WORKER, OUTSIDER, ALCOHOLIC
    };

private:
    int     position;
    int     energy;
    bool    bankrupt;
    bool    mobile;
    int     panelty;
    std::list<Block>   own_blocks;
    CharacterType character_type;

public:
    Player();
    ~Player();

    int getPosition() const;
    bool isMobile() const;
    int getEnergy() const;

    void setPosition(int position);
    void moveTo(int position);
    bool checkWinStatus();
    bool checkMouindo();
    bool escapeMouindo();
    bool hasBlock(Block block);
    void buyBlock(Block block);
    void sellBlock(Block block);

};
      
