#include "player.h"

using namespace std;

Player::Player(int HP, int Atk, int Def, string Race, char Kind, Tile *parent): 
Character(HP, Atk, Def,'@', parent), gold(0), Race(Race) {};

Player::Player(int HP, int Atk, int Def, char Kind, Tile *parent): 
Character(HP, Atk, Def,'@', parent), gold(0){};

string Player::getRace(){
	return Race;
}

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

void Player::getGold(Treasure *t){

	if (Race == "dwarf"){ // double gold for dwarves ayyy
		gold += 2*(t->getValue());

	} else if ( Race == "orc"){ // half gold for orcs lmao
		gold += 0.5*(t->getValue());

	}else{ // rest of the races 
		gold += t->getValue();
	}
}
