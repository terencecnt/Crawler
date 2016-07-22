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

void Character::changeHP(int n){
    int newHP = HP + n;
    if (newHP > HP){
        cout << "need a variable for MaxHP" << endl;
    }else if ( newHP < 0){
        HP = 0;
    }else{
        HP = newHP;
    }
}