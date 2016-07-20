#ifndef _ENEMY_
#define _ENEMY_
#include "character.h"

class Enemy: public Character{
  public: 
      Enemy(int HP, int Atk, int Def,char Kind, Tile *parent); 
      ~Enemy() = default; 
};

class Vampire: public Enemy { 
    Vampire(); 
    ~Vampire(); 

};






#endif

