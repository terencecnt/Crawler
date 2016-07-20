#include "object.h"
#include <iostream>
using namespace std;

Object:: Object(char kind, Tile *parent): kind{kind}, parent{parent}{
//cout << kind; 
}

char Object::getKind() {
 //   cout << "calling getkind" << endl;
    return kind;
}

Tile *Object::getParent() {
    return parent;
}

void Object::changeParent(Tile *new_parent) {
    parent = new_parent;
}


