#ifndef _ENEMY_
#define _ENEMY_
#include <memory>
#include "character.h"

class Enemy: public Character{
  public: 
      Enemy(int HP, int Atk, int Def,char Kind, Tile *parent); 
      virtual ~Enemy(); 
};

class Vampire: public Enemy { 
    public:
    Vampire(Tile *parent); 
    ~Vampire() = default;

};

class Merchant: public Enemy {
    bool hostile;
    public:
    bool checkHostile(); 
    void makeHostile();
    Merchant(Tile *parent); 
    ~Merchant() = default;
};

class Werewolf: public Enemy { 
    public:
        Werewolf(Tile *parent); 
        ~Werewolf() = default;
};

class Goblin: public Enemy { 
    public:
        Goblin(Tile *parent); 
        ~Goblin() = default;
};

class Phoenix: public Enemy {
    public:
        Phoenix(Tile *parent);
        ~Phoenix() = default;
};

class Troll: public Enemy {
    public:
        Troll(Tile *parent); 
        ~Troll() = default;
};

class dragonGold;

class Dragon: public Enemy {
    std::shared_ptr<dragonGold> son;
    public:
        Dragon(Tile *parent,std::shared_ptr<dragonGold> son);
        void notifyGold();
        ~Dragon() = default;
};



#endif

