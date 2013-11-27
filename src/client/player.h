#pragma once
#include <list>
#include <map>
#include "block.h"
#include "subjectblock.h"

// circular dependency
class Block;
class SubjectBlock;


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
    bool    mobile;                    // is player movable? (Mouindo, Drink...)
    int     panelty;                   // how long to be punished 
    bool    plural;                    // plural major status
    std::map<SubjectBlock::Department, int> registered;     // registered class for each subject
    std::list<Block*> own_blocks;
    CharacterType character_type;

public:
    Player();
    ~Player();

    int  getPosition() const;
    bool isBankrupt() const;
    bool isMobile() const;
    int  getEnergy() const;
    int  getPanelty() const;
    bool isPlural() const;
    CharacterType getCharacterType() const;

    void setPosition(int position);
    void setEnergy(int getenergy);
    void setPlural(bool plural);
    void setMouindo(int panelty);
    bool escapeMouindo();
    void moveTo(int dice);

    bool hasBlock(Block* block);
    void buyBlock(Block* block);
    void sellBlock(Block* block);
    void takeBlock(Block* block);
    void loseBlock(Block* block);
    void giveSalary();

    bool checkWinStatus();
};
      
