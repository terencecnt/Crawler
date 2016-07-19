#include "elf.h" 

Elf::Elf(Tile *parent): Player{140,30,10, '@', parent} {}

void Elf::usePotion(Potion *p) {
    if (p->getType() == 'H') {
        HP += abs(p->getValue());
        
    }
    if (p->getType() == 'A') {
        Atk += abs(p->getValue());
    }
    if (p->getType() == 'D') {
        Def += abs(p->getValue());
        
    }
}
