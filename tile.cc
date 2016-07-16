#include "grid.h"
#include "tile.h"
using namespace std;

Tile::Tile(int row, int column, TextDisplay *td, Object *content): row{row}, column{column}, td{td}, content{content}{}

int Tile::getColumn() {
    return column;
}

int Tile::getRow() {
    return row;
}

void Tile:: attach(Tile *o) {
    neighbors.emplace_back(o);
}

Object *Tile:: getObject() {
    return content;
}
