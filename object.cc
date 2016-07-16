#include "object.h"

Object:: Object(char kind, Tile *parent): kind{kind}, parent{parent}{}

char Object::getKind() {
    return kind;
}
