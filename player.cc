#include "player.h"

Player::Player(int HP, int Atk, int Def, char Kind, Tile *parent): Character(HP, Atk, Def, '@', parent), gold{0} {};

void Player::usePotion(Potion *p) {
    if (p->getType() == 'H') {
        HP += p->getValue();
        
    }
    if (p->getType() == 'A') {
        Atk += p->getValue();
    }
    if (p->getType() == 'D') {
        Def += p->getValue();
        
    }
}
