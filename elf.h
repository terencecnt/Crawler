#ifndef _ELF_
#define _ELF_
#include "player.h"
#include<memory>

class Elf: public Player{
    public:
    Elf(Tile *parent); 
    void usePotion(std::shared_ptr<Potion> p);
};

#endif
