#ifndef _PLAYER_
#define _PLAYER_
#include "character.h"
#include "potion.h"
#include "treasure.h"

class Player: public Character {
    int gold; 
    std::string Race;
    public: 
    Player(int HP, int Atk, int Def, std::string Race, char Kind, Tile *parent); 
    ~Player() = default; 
    std::string getRace();
    virtual void usePotion(Potion *p);
    virtual void getGold(Treasure *t);
};

#endif
