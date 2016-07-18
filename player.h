#ifndef _PLAYER_
#define _PLAYER_
#include "character.h"

class Player: public  Character {
    int gold; 
    public: 
    Player(int HP, int Atk, int Def, char Kind, Tile *parent); 
    ~Player() = default; 
};

#endif
