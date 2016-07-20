#include "enemy.h"

Enemy:: Enemy(int HP, int Atk, int Def,char Kind, Tile *parent):
    Character(HP, Atk, Def,Race, Kind, Parent); {}

Enemy:: ~Enemy(){};

Vampire::Vampire() { 
    Enemy{50,25,25, 'V', parent} {}
}

Merchant::Merchant(){ 
    Enemy{30, 70, 5, 'M', parent} {}
}

Werewolf::Werewolf{
    Enemy{120,30,5,'W', parent} {}
}

Goblin::Goblin {
    Enemy{70,5,10,'G', parent} {}
}

Troll::Troll{
    Enemy{120,25,15. 'T', parent} {}
}


