#include "character.h"
using namespace std;
Character::Character(int HP, int Atk, int Def, char Kind, Tile *parent): 
HP{HP}, Atk{Atk}, Def{Def},Object{Kind, parent} {}


int Character::getHP() {
    return HP;
}

int Character::getAtk(){
    return Atk;
}
int Character::getDef(){
    return Def;
}

int Character::changeHP(int n, string to_change){
    HP = n;
    return HP;
}

void Character::changeATK(int n) {
    Atk += n;
}

void Character::changeDEF(int n) {
    Def += n;
}
