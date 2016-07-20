#include "enemy.h"

Enemy:: Enemy(int HP, int Atk, int Def,char Kind, Tile *parent):
    Character(HP, Atk, Def,Race, Kind, Parent); {}

Vampire::Vampire() { 
    Enemy{50,25,25, 'V', parent} {}
}

