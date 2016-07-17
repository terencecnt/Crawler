#ifndef _OBJECT_
#define _OBJECT_
#include "tile.h"

class Tile;

class Object {
    char kind;
    Tile *parent;
public: 
    Object(char kind, Tile *parent); 
    char getKind();
    ~Object() = default;
    Tile *getParent();
    void changeParent(Tile *parent);
};

#endif
