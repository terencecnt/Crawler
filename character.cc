#include "character.h"
using namespace std;
Character::Character(int HP, int Atk, int Def,  char Kind, Tile *parent): HP{HP}, Atk{Atk}, Def{Def},Object{Kind, parent} {}
