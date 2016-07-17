#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "grid.h"
#include<iostream>
#include<string>
using namespace std;

Grid:: Grid() {
    floor = 0;
    int row = 25;
    int column =79;
    for (int i= 0; i < row; ++i) {
        vector<Tile> row;
        for (int j =0; j < column; ++j) {
           // cout << Tile(i,j).getObject()->getKind() << "Wtf" << endl;
            row.emplace_back(Tile(i,j));
        }
     //neighbors function here
        Board.emplace_back(row);
//        cout << endl;
    }

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            if (((j - 1) >= 0)) {
                Board[i][j].attach(&Board[i][j-1]);
            } else {
                nullptr;
            }
            
            if (((i - 1) >= 0) && ((j - 1) >= 0)) {
                Board[i][j].attach(&Board[i - 1][j - 1]);
            } else {
                nullptr;
            }
    
            if ((i - 1) >= 0) {
                Board[i][j].attach(&Board[i-1][j]);
            } else {
                nullptr;
            }
            if (((i - 1) <= row) && ((j+1) <= column)) {
                Board[i][j].attach(&Board[i-1][j + 1]);
            } else {
                nullptr;
            }
            if ((j+1) <= column) {
                Board[i][j].attach(&Board[i][j + 1]);
            } else {
                nullptr;
            }
            if (((i + 1) <= row) && ((j+1) <= column)) {
                Board[i][j].attach(&Board[i][j + 1]);
            } else {
                nullptr;
            }
            if ((i + 1) <= row) {
                Board[i][j].attach(&Board[i][j + 1]);
            } else {
                nullptr;
            }
            if (((i + 1) <= row) && ((j-1) >= 0)) {
                Board[i][j].attach(&Board[i][j + 1]);
            } else {
                nullptr;
            }
        }
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



















































































































































































































void Grid::swapObject(Tile *t1, Tile *t2) {
        Object *temp = t1->getObject();
        t1->changeO(t2->getObject());
        t2->changeO(temp);
}
    
void Grid:: move(string d) {
    try {
        Tile *to_move_to = player->getParent()->getneighbor(d);
        char kind = to_move_to->getObject()->getKind();
        if ((to_move_to == nullptr)||
                ((kind != 'G')&&
                 (kind != '.')&&
                 (kind != '/'))) {
                    throw "error";
                } else {
                    swapObject(to_move_to, player->getParent());
                }
        }
    catch(...) {
        cout << "Unable to move to " << d << endl;
    }
}
