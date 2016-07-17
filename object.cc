#include "object.h"
#include <iostream>
using namespace std;

Object:: Object(char kind, Tile *parent): kind{kind}, parent{parent}{
cout << kind; 
}

char Object::getKind() {
    return kind;
}
