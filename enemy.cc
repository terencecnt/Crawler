#include "enemy.h"
#include "treasure.h"
using namespace std;

Enemy:: Enemy(int HP, int Atk, int Def,char Kind, Tile *parent): Character(HP, Atk, Def, Kind, parent) {
    if (Kind == 'V') {
        name = "Vampire";
    } else if (Kind == 'N') {
        name = "Goblin";
    } else if (Kind == 'M') {
        name = "Merchant";

    } else if (Kind == 'D') {
        name = "Dragon";

    } else if (Kind == 'X') {
        name = "Phoenix";

    } else if (Kind == 'W') {
        name = "Werewolf";
        
    } else if (Kind == 'T') {
        name = "Troll";
    }
};

Enemy:: ~Enemy(){};

string Enemy:: getName() {
    return name;
}
Vampire::Vampire(Tile *parent): Enemy{50,25,25, 'V', parent} {}
Merchant::Merchant(Tile *parent) : Enemy{30, 70, 5, 'M', parent}, hostile{false} {}

bool Merchant::checkHostile() { return hostile;}
void Merchant::makeHostile() { hostile = true;}

Werewolf::Werewolf(Tile *parent):  Enemy{120,30,5,'W', parent} {}

Goblin::Goblin(Tile *parent): Enemy{70,5,10,'N', parent} {}

Troll::Troll(Tile *parent):  Enemy{120,25,15, 'T', parent} {}

Phoenix::Phoenix(Tile *parent): Enemy{50, 35, 20, 'X', parent}{}

Dragon::Dragon(Tile *parent, shared_ptr<dragonGold> son): Enemy{150, 20, 20, 'D', parent}, son{son} {}

void Dragon::notifyGold(){
        son->changeStatus();
}

bool Dragon::can_be_son(shared_ptr<dragonGold> could_be_son) {
    //check if could_be_son is a neighbour of Dragon
    //check west
    for (int i =0; i <8; ++i) {
        if (this->getParent()->getneighbor("false", i) == could_be_son->getParent()) {
            return true;
        }
    } 
    return false;
}

void Dragon::updateSon(shared_ptr<dragonGold> new_son) {
    son = new_son;
}
