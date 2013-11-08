#pragma once

class Player
{
public:
    enum CharacterType {
        LOL, GENIUS, HARD_WORKER, OUTSIDER, ALCOHOLIC
    };

private:
    int     location;
    int     energy;
    int     position;
    bool    bankrupt;
    bool    mobile;
    CharcterType character_type;


public:
    Player();
    ~Player();

    int getPosition();
    bool isMobile();

    void moveTo(int position);
    void setPosition(int position);
    bool checkWinStatus();

};
