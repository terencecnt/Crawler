#include "treasure.h"

#include <iostream>
using namespace std;


Treasure::Treasure(int value, Tile* parent): Object('G' , parent) , value(value) {}
Treasure::~Treasure(){}
int Treasure::getValue() { return value; }


Normal::Normal(Tile* parent): Treasure(1, parent) {}
Normal::~Normal() {}


Small::Small(Tile* parent): Treasure(2, parent) {}
Small::~Small() {}


merchantGold::merchantGold(Tile* parent): Treasure(4, parent) {}
merchantGold::~merchantGold() {}


dragonGold::dragonGold(Tile* parent): Treasure(6, parent) {}
void dragonGold::updateDragon(shared_ptr<Dragon> father) {
    owner = father;
}
dragonGold::~dragonGold() {}
