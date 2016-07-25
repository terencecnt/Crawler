#include "enemy.h"
#include "treasure.h"
using namespace std;

Enemy:: Enemy(int HP, int Atk, int Def,char Kind, Tile *parent): Character(HP, Atk, Def, Kind, parent) {};

Enemy:: ~Enemy(){};

Vampire::Vampire(Tile *parent): Enemy{50,25,25, 'V', parent} {}
Merchant::Merchant(Tile *parent) : hostile{false}, Enemy{30, 70, 5, 'M', parent} {}

bool Merchant::checkHostile() { return hostile;}
void Merchant::makeHostile() { hostile = true;}

Werewolf::Werewolf(Tile *parent):  Enemy{120,30,5,'W', parent} {}

Goblin::Goblin(Tile *parent): Enemy{70,5,10,'N', parent} {}

Troll::Troll(Tile *parent):  Enemy{120,25,15, 'T', parent} {}

Phoenix::Phoenix(Tile *parent): Enemy{50, 35, 20, 'X', parent}{}

Dragon::Dragon(Tile *parent, shared_ptr<dragonGold> son): son{son}, Enemy{150, 20, 20, 'D', parent}  {}

void Dragon::notifyGold(){
        son->changeStatus();
}

bool Dragon::can_be_son(shared_ptr<dragonGold> could_be_son) {

