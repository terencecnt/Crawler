#include <iostream>
#include "grid.h"
using namespace std;

Grid:: Grid() {
    floor = 0;
    td = nullptr;
    for (int i= 0; i < 30; ++i) {
	    vector<Tile> row; 
	    for (int j =0; j < 79; ++j) {
		
		    row.emplace_back(Tile(i,j));
	    }
	    cout << endl;
	    Board.emplace_back(row);
    }
}

Grid::~Grid() {
    delete td;
}

void Grid:: print() {
    td->print();
}

