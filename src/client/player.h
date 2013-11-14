#pragma once

class Player
{
public:
    enum CharacterType {
        NONE, LOL, GENIUS, HARD_WORKER, OUTSIDER, ALCOHOLIC
    };

private:
    int     location;
    int     energy;
    int     position;
    bool    bankrupt;
    bool    mobile;
    int     panelty;
    CharcterType character_type;

public:
    Player();
    ~Player();

    int getPosition() const;
    bool isMobile() const;

    void setPosition(int position);
    void moveTo(int position);
    bool checkWinStatus();
    bool checkMouindo();
    bool escapeMouindo();
};
