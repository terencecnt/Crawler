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
    ~Vampire() = default;

};

class Merchant: public Enemy {
    Merchant(Tile *parent); 
    ~Merchant() = default;
};

class Werewolf: public Enemy {
    Werewolf(Tile *parent); 
    ~Werewolf() = default;
};

class Goblin: public Enemy { 
    Goblin(Tile *parent); 
    ~Goblin() = default;
};

class Phoenix: public Enemy {
    Phoenix(Tile *parent);
    ~Phoenix() = default;
};

class Troll: public Enemy {
    Troll(Tile *parent); 
    ~Troll() = default;
};

class Dragon: public Enemy {
    Dragon(Tile *parent);
    ~Dragon() = default;
}



#endif

