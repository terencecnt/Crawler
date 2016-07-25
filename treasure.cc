#include "treasure.h"

#include <iostream>
using namespace std;


Treasure::Treasure(int value, Tile* parent): Object('G' , parent) , value(value) {
}
Treasure::~Treasure(){}
int Treasure::getValue() { return value; }


Normal::Normal(Tile* parent): Treasure(1, parent) {}
Normal::~Normal() {}


Small::Small(Tile* parent): Treasure(2, parent) {}
Small::~Small() {}


merchantGold::merchantGold(Tile* parent): Treasure(4, parent) {}
merchantGold::~merchantGold() {}


dragonGold::dragonGold(Tile* parent): Treasure(6, parent), alive{true} {}

void dragonGold::updateDragon(weak_ptr<Dragon> father) {
    owner = father;
  //  cout << "Row:" <<  parent->getRow() << "Col:" << parent->getColumn()<< endl;
}
bool dragonGold::isAlive(){
    return alive;
}
void dragonGold::changeStatus() { 
    alive= false;
}


dragonGold::~dragonGold() {}
