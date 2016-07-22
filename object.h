#ifndef _OBJECT_
#define _OBJECT_
#include "tile.h"

class Tile;

class Object {
    char kind;
 protected:
    Tile *parent;
public: 
    Object(char kind, Tile *parent); 
    char getKind();
    virtual ~Object()= default;
    Tile *getParent();
    void changeParent(Tile *new_parent);
};

#endif
