#include "enemy.h"

Enemy:: Enemy(int HP, int Atk, int Def,char Kind, Tile *parent): Character(HP, Atk, Def,Race, Kind, parent) {};


Enemy:: ~Enemy(){};

Vampire::Vampire(Tile *parent): Enemy{50,25,25, 'V', parent} {}

Merchant::Merchant(Tile *parent) :  Enemy{30, 70, 5, 'M', parent} {}

Werewolf::Werewolf(Tile *parent):  Enemy{120,30,5,'W', parent} {}

Goblin::Goblin(Tile *parent): Enemy{70,5,10,'G', parent} {}

Troll::Troll(Tile *parent):  Enemy{120,25,15. 'T', parent} {}

Phoenix::Phoenix(Tile *parent): Enemy{50, 35, 20, 'P', parent}{}

Dragon::Dragon(Tile *parent): Enemy{150, 20, 20, 'D', parent}{}
