#ifndef _PLAYER_TWO_
#define _PLAYER_TWO_
#include "player.h"
#include<memory>

class Elf: public Player{
    public:
    Elf(Tile *parent);
    void usePotion(std::shared_ptr<Potion> p);
};

class Dwarf: public Player{
    public:
    Dwarf(Tile *parent);
};

class Orc: public Player{
    public:
    Orc(Tile *parent);
};

class Human: public Player{
    public:
    Human(Tile *parent);
};

#endif
