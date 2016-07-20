#ifndef _ENEMY_
#define _ENEMY_
#include "character.h"

class Enemy: public Character{
  public: 
      Enemy(int HP, int Atk, int Def,char Kind, Tile *parent); 
      virtual ~Enemy() = 0; 
};

class Vampire: public Enemy { 
    Vampire(Tile *parent); 
    ~Vampire(); 

};

class Merchant: public Enemy {
    Merchant(Tile *parent); 
    ~Merchant();
};

class Werewolf: public Enemy {
    Werewolf(Tile *parent); 
    ~Werewolf();
};

class Goblin: public Enemy { 
    Goblin(Tile *parent); 
    ~Goblin(); 
};

class Phoenix: public Enemy {
    Phoenix(Tile *parent);
    ~Phoenix(); 
};

class Troll: public Enemy {
    Troll(Tile *parent); 
    ~Troll(); 
};





#endif

