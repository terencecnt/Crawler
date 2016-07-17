#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "grid.h"
using namespace std;

Grid:: Grid() {
    floor = 0;
   // td = nullptr;
    for (int i= 0; i < 25; ++i) {
	    vector<Tile> row; 
	    for (int j =0; j < 79; ++j) {
		    row.emplace_back(Tile(i,j));
	    }
     //neighbors function here
	//    cout << endl;
	    Board.emplace_back(row);
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
        row = rand()%24;
        col = rand()%78;
       // cout << "row: " << row << " col: " << col << endl;
       // cout << Board[row][col].getObject()->getKind()  << endl;   
        if (Board[row][col].getObject()->getKind() == '.') 
        //compare rooms

        
        { 
         //       cout << "lol we found it" << endl;
                Object temp('/', &Board[row][col]);
                Board[row][col].changeO(&temp);
                return;
            }
    }
}


/*
void Grid::initPlayer() {
    Player player(); 
    bool invalid= true;
    int row;
    int col; 
    while (invalid) { 
        //srand(time(NULL));
        row = rand()%24;
        col = rand()%78;
        cout << Board[row][col].getObject()->getKind()  << endl;   
        if (Board[row][col].getObject()->getKind() == '.') { 
                Board[row][col].changeO(player);
                return;
            }
    }
}
*/






void Grid:: print() {
    td->print();
}

