#include "treasure.h"

#include <iostream>
using namespace std;


Treasure::Treasure(const int value, Tile* parent): Object('G' , parent) , value(value) {}
Treasure::~Treasure(){}


Normal::Normal(Tile* parent): Treasure(1, parent) {}
Normal::~Normal() {}
Normal::getValue() { return value; }

Small::Small(Tile* parent): Treasure(2, parent) {}
Small::~Small() {}
Small::getValue() { return value; }

merchantGold::merchantGold(Tile* parent): Treasure(4, parent) {}
merchantGold::~merchantGold() {}
merchantGold::getValue() { return value; }

dragonGold::dragonGold(Tile* parent, Dragon* dragon): Treasure(6, parent) , dragon(dragon){}
dragonGold::~dragonGold() {}
dragonGold::getValue() { return value; }