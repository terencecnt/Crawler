#ifndef _ENEMY_
#define _ENEMY_
#include "character.h"

class Enemy: public Character{
  public: 
      Enemy(int HP, int Atk, int Def,char Kind, Tile *parent); 
      virtual ~Enemy() = 0; 
};

class Vampire: public Enemy { 
    Vampire(); 
    ~Vampire(); 

};

class Merchant: public Enemy {
    Merchant(); 
    ~Merchant();
};

class Werewolf: public Enemy {
    Werewolf(); 
    ~Werewolf();
};

class Goblin: public Enemy { 
    Goblin(); 
    ~Goblin(); 
};

class Phoenix: public Enemy {
    Phoenix();
    ~Phoenix(); 
};

class Troll: public Enemy {
    Troll(); 
    ~Troll(); 
};





#endif

