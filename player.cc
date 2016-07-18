#include "player.h"

Player::Player(int HP, int Atk, int Def, char Kind, Tile *parent): Character(HP, Atk, Def, '@', parent), gold{0} {};
