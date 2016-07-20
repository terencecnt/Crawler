#ifndef _CHARACTER_
#define _CHARACTER_
#include "object.h"

class Character: public Object {
    protected:
    int HP; 
    int Atk;
    int Def; 
    public: 
    Character(int HP, int Atk, int Def, char Kind, Tile *parent);
    ~Character() = default; 
   // void move(); 
   // virtual void slay(); 
   // virtual void attacked(); 
};

#endif

