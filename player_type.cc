#include <string>
#include "player_type.h"
#include "player.h"
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

Dwarf::Dwarf(Tile *parent): Player{100,20,30, "dwarf",  '@', parent} {}

Orc::Orc(Tile *parent): Player{180,30,25, "orc", '@', parent} {}

Human::Human(Tile *parent): Player{140,20,20, "human",'@', parent} {}
