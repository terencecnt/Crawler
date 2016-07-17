#include "textdisplay.h"
#include "tile.h"
#include "grid.h"
#include "object.h"
#include <iostream>
using namespace std; 


int main () {
    Grid g;
    g.initStair();
    g.initPlayer();
    g.print();
}
