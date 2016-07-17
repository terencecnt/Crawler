#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "grid.h"
#include<iostream>
#include<string>
#include "player.h"
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
               Board[i][j].attach(nullptr);
            }
            
            if (((i - 1) >= 0) && ((j - 1) >= 0)) {
                Board[i][j].attach(&Board[i - 1][j - 1]);
            } else {
                Board[i][j].attach(nullptr);
            }
    
            if ((i - 1) >= 0) {
                Board[i][j].attach(&Board[i-1][j]);
            } else {
                Board[i][j].attach(nullptr);
            }
            if (((i - 1) <= row) && ((j+1) <= column)) {
                Board[i][j].attach(&Board[i-1][j + 1]);
            } else {
                Board[i][j].attach(nullptr);
            }
            if ((j+1) <= column) {
                Board[i][j].attach(&Board[i][j + 1]);
            } else {
                Board[i][j].attach(nullptr);
            }
            if (((i + 1) <= row) && ((j+1) <= column)) {
                Board[i][j].attach(&Board[i][j + 1]);
            } else {
                Board[i][j].attach(nullptr);
            }
            if ((i + 1) <= row) {
                Board[i][j].attach(&Board[i][j + 1]);
            } else {
                Board[i][j].attach(nullptr);
            }
            if (((i + 1) <= row) && ((j-1) >= 0)) {
                Board[i][j].attach(&Board[i][j + 1]);
            } else {
                Board[i][j].attach(nullptr);
            }
        }
    }    
    shared_ptr<TextDisplay>theDisplay = make_shared<TextDisplay>(TextDisplay(Board, floor));
    td = theDisplay;
}

Grid::~Grid() {
}

void Grid::initStair() {
    int row;
    int col;
    srand(time(NULL));
    while (true) {
        row = rand()%24;
        col = rand()%78;
        if (Board[row][col].getObject()->getKind() == '.') {
            auto temp = make_shared<Object>(Object('/', &Board[row][col]));
            Board[row][col].changeO(temp);
            td->update(Board[row][col]);
            return;
        }
    }
}

void Grid::initPlayer() {
    int row;
    int col;
    srand(time(NULL));
    while (true) {
        row = rand()%24;
        col = rand()%78;
        if (Board[row][col].getObject()->getKind() == '.') {
            auto temp = make_shared<Object>(Player(&Board[row][col]));
            Board[row][col].changeO(temp);
            td->update(Board[row][col]);
            return;
        }
    }
}

void Grid:: print() {
    td->print();
}

void Grid::swapObject(Tile *t1, Tile *t2) {
        auto temp = t1->getObject();
        auto temp_two = t2->getObject();
        temp->changeParent(t2);
        temp_two->changeParent(t1);
        t1->changeO(temp_two);
        t2->changeO(temp);
}
    
void Grid:: move(string d) {
    try {
        auto to_move_to = player->getParent()->getneighbor(d);
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
