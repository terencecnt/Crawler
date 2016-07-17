#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "grid.h"
#include<iostream>
#include<string>
using namespace std;

Grid:: Grid() {
    floor = 0;
    for (int i= 0; i < 25; ++i) {
        vector<Tile> row;
        for (int j =0; j < 79; ++j) {
           // cout << Tile(i,j).getObject()->getKind() << "Wtf" << endl;
            row.emplace_back(Tile(i,j));
        }
     //neighbors function here
        Board.emplace_back(row);
//        cout << endl;
    }

    TextDisplay *theDisplay = new TextDisplay(Board, floor);
    td = theDisplay;

}

Grid::~Grid() {
    delete td;
    // delete all Tiles, they are in heap, or smart pointers
}

void Grid::initStair() {
    int row;
    int col;
    while (true) {
        row = rand()%24;
        col = rand()%78;
        if (Board[row][col].getObject()->getKind() == '.') {
            Object temp('/', &Board[row][col]);
            Board[row][col].changeO(&temp);
            td->update(Board[row][col]);
            return;
        }
    }
}

void Grid:: print() {
    td->print();
}



























































































































































































































































void Grid:: move(string d) {
    try {
        Tile *to_move_to = player->getneighbor(d);
        char kind = to_move_to->getObject()->getKind();
        if ((to_move_to == nullptr)||
            ((kind != 'G')&&
             (kind != '.')&&
             (kind != '/'))) {


            throw "error";
        }

    }
    catch(...) {
        cout << "Unable to move to " << d << endl;
    }
}





