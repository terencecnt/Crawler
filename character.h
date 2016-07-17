#ifndef _CHARACTER_
#define _CHARACTER_
#include "object.h"

class Character: public Object {
    int HP; 
    int Atk;
    int Def; 
    string Race;
    public: 
    Character();
    ~Character(); 
    string getType();
    void move(); 
    virtual slay(); 
    virtual attacked(); 
}

#endif

