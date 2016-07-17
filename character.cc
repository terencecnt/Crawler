#include "character.h"
using namespace std;
Character::Character(int HP, int Atk, int Def, string Race, char Kind, Tile *parent): HP{HP}, Atk{Atk}, Def{Def}, Race{Race}, Object{Kind, parent} {}
