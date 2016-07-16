#include <iostream>
#include "grid.h"
using namespace std;

Grid:: Grid() {
    floor = 0;
    td = nullptr;

}

Grid::~Grid() {
    delete td;
}

void Grid:: print() {
    td->print();
}

