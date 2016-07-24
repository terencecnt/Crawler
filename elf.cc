#include "elf.h"
#include <string>
using namespace std;

Elf::Elf(Tile *parent): Player{140,30,10, "elf", '@', parent} {}

void Elf::usePotion(shared_ptr<Potion> p) {
    if ((p->getType())[0] == 'H') {
        HP += abs(p->getValue());
        
    }
    if ((p->getType())[0] == 'A') {
        Atk += abs(p->getValue());
    }
    if ((p->getType())[0] == 'D') {
        Def += abs(p->getValue());
        
    }
}
