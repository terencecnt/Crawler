#ifndef _ENEMY_
#define _ENEMY_
#include "character.h"

class Enemy: public Character{
    public: 
        Enemy(); 
        ~Enemy();
        void move(); 
};


#endif

