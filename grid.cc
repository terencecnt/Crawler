#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "grid.h"
using namespace std;

Grid:: Grid() {
    floor = 0;
    td = nullptr;
    for (int i= 0; i < 25; ++i) {
	    vector<Tile> row; 
	    for (int j =0; j < 79; ++j) {
		
		    row.emplace_back(Tile(i,j));
	    }
     //neighbors function here
	    cout << endl;
	    Board.emplace_back(row);
    }
}

Grid::~Grid() {
    delete td;
}

Grid::initStair() {
    bool invalid= true;
    int row;
    int col; 
    while (invalid) { 
        srand(time(NULL));
        row = rand()%24;
        col = rand()%78;
        cout << "row: " << row << " col: " << col << endl;
            if (Board[row][col].getKind() == '.') {
                invalid = false; 
            }
            Object temp('/', &Board[row][col]);
            Board[row][col].changeO(&temp);
    }




void Grid:: print() {
    td->print();
}

