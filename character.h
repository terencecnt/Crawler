#ifndef _CHARACTER_
#define _CHARACTER_
#include "object.h"

class Character: public Object {
    int HP; 
    int Atk;
    int Def; 
    std::string Race;
    public: 
    Character(int HP, int Atk, int Def, char Kind, Tile *parent);
    ~Character() = default; 
    std::string getType();
   // void move(); 
   // virtual void slay(); 
   // virtual void attacked(); 
};

#endif

