#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "grid.h"
#include<iostream>
using namespace std;

Grid:: Grid() {
    floor = 0;
<<<<<<< HEAD
   // td = nullptr;
    for (int i= 0; i < 25; ++i) {
	    vector<Tile> row; 
	    for (int j =0; j < 79; ++j) {
		    row.emplace_back(Tile(i,j));
	    }
     //neighbors function here
	//    cout << endl;
=======
    for (int i= 0; i < 25; ++i) {
	    vector<Tile> row; 
	    for (int j =0; j < 79; ++j) {
           // cout << Tile(i,j).getObject()->getKind() << "Wtf" << endl;
		    row.emplace_back(Tile(i,j));
	    }
     //neighbors function here 
>>>>>>> 2593e71a71d88da2cf723a7454cd1f7c6cd17d7d
	    Board.emplace_back(row);
//        cout << endl;
    }
<<<<<<< HEAD

    TextDisplay *theDisplay = new TextDisplay(Board, floor); 
    td = theDisplay;
=======
    
    TextDisplay *theDisplay = new TextDisplay(Board, floor);
    td = theDisplay;
    
>>>>>>> 2593e71a71d88da2cf723a7454cd1f7c6cd17d7d
}

Grid::~Grid() {
    delete td;
}
/*
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
<<<<<<< HEAD


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






=======
*/
>>>>>>> 2593e71a71d88da2cf723a7454cd1f7c6cd17d7d
void Grid:: print() {
    td->print();
}

