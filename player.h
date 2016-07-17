#ifndef _PLAYER_
#define _PLAYER_
#include "character.h"

class Player: public  Character {
    int gold; 
    public: 
    Player(); 
    ~Player(); 
};

#endif
