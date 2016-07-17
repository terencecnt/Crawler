#ifndef _OBJECT_
#define _OBJECT_
#include "tile.h"

class Tile;

class Object {
    char kind;
    Tile  *parent;
    ~Object() = default;
public: 
    Object(char kind, Tile *parent); 
    char getKind();
};

#endif
