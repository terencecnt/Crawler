#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "grid.h"
#include<iostream>
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
}

void Grid::initStair() {
    bool invalid= true;
    int row;
    int col;
    while (invalid) {
       srand();
        row = rand()%24;
        col = rand()%78;
 //       cout << "row: " << row << " col: " << col << endl;
        
        if (Board[row][col].getObject()->getKind() == '.') {
                invalid = false;
            }
            Object temp('/', &Board[row][col]);
            Board[row][col].changeO(&temp);
    }
}

void Grid:: print() {
    td->print();
}
