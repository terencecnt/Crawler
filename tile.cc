#include "grid.h"
#include "tile.h"
#include<string>
using namespace std;

Tile::Tile(int row, int col): row{row}, col{col} {
	if (((col == 0 || col == 78) && (row <= 24)) || ((col == 2) && (((row >= 2) && (row <= 7)))) || ((col == 3) && ((row >= 14) && (row <= 22))) || (((col == 29) || (col == 38)) && (((row== 2) || (row == 3)) || ((row >= 5) && (row <= 7)))) || ((col == 25) && (((row >= 14) && (row <= 19)) || ((row == 21) || (row == 22)))) || ((col == 36) && (((row >= 18) && (row <= 19)) || ((row == 21) || (row == 22)))) || (((col == 37) || (col == 50)) && ((row >= 9) && (row <= 13))) || ((col == 60) && (((row >= 7) && (row <= 10)) || ((row == 12) || (row == 13)))) || ((col == 62) && (((row >= 2) && (row <= 4))))|| ((col == 64) && (((row >= 15) && (row <= 18)))) || ((col == 70) && ((row == 4) || (row == 5))) || ((col == 73) && ((row == 5) || (row == 6))) || ((col == 76)  && ((((row >= 6) && (row <= 13)))|| ((row >= 15) && (row <= 22))))) { 
		
       content = make_shared<Object>(Object('|', this));
	}

	else if ((row== 0) || (row == 24)) {
       content = make_shared<Object>(Object('-', this));
	}

	else if (((row==7 ) && (col == 13)) ||
		((row ==14 ) && (col ==13)) ||
		((row == 4) && (col == 38)) || 
		((row == 7) && (col == 43)) ||
		((row == 13) && (col == 43))||
		((row ==18 ) && (col ==43 )) || 
		((row ==11 ) && (col ==60 )) ||
		((row == 13) && (col ==69)) ||
		((row ==15 ) && (col ==69)) ||
		((row ==20) && (col ==25)) ||
		((row ==20) && (col ==36)) ||
		((row==9 ) && (col == 43)) ||
		((row==4) && (col == 29))) {
		
       content = make_shared<Object>(Object('+', this));
	}

	else if (((row== 4) && ((col >= 30) && (col <= 37))) ||  
			((row== 8) && ((col >= 31) && (col <= 43))) ||
			((row== 20) && ((col >= 26) && (col <= 35))) ||
			((row== 11) && ((col >= 13) && (col <= 31))) || 
			((row== 11) && ((col >= 54) && (col <= 59))) ||
			((row== 16) && ((col >= 31) && (col <= 54))) ||
			((col == 13) && ((row >= 8) && (row <= 13))) ||
			((col == 33) && ((row >= 5) && (row <= 7))) ||
			((col == 31) && ((row >= 8) && (row <= 20))) ||
			((col == 43) && ((row >= 14) && (row <= 17))) ||
			((col == 54) && ((row >= 12) && (row <= 15))) ||
			((col == 69) && (row== 14))) {
		
       content = make_shared<Object>(Object('#', this));
	}

	//horizontal wallz
	else if ((row== 2) &&  ((col >= 3 && col <29) || (col >= 39 && col <62))) {
       content = make_shared<Object>(Object('-', this));
	}else if ((row==4) &&  (col >= 63 && col <70)){
       content = make_shared<Object>(Object('-', this));
	}else if ((row==5) && (col >= 71 && col <73)){
        content = make_shared<Object>(Object('-', this));
	}else if ((row==6) && (col >= 74 && col <76)){	
        content = make_shared<Object>(Object('-', this));
	}else if ((row== 7) && ((col >= 3 && col <13) || (col >= 14 && col <29) || (col >= 39 && col < 43 )|| (col >= 44 && col < 60))){
        content = make_shared<Object>(Object('-', this));

	}else if ((row== 9) && ((col >= 38 && col < 43) || (col >= 44 && col < 50)))  {
        content = make_shared<Object>(Object('-', this));

	}else if ((row== 13) && ((col >= 38 && col < 50 && col != 43) || (col >= 62 && col < 76 && col != 69))){
        content = make_shared<Object>(Object('-', this));
	}else if ((row== 14) && (col >= 4 && col <25 && col != 13)) {
        content = make_shared<Object>(Object('-', this));
	}else if ((row== 15) && ( col >= 65 && col <76 && col != 69)){
        content = make_shared<Object>(Object('-', this));
	}else if ((row== 18) && (col >= 37 && col <64 && col != 43)){
        content = make_shared<Object>(Object('-', this));
	}else if ((row== 22) && ((col >= 4 && col <25) || (col >= 37 && col <76))){
        content = make_shared<Object>(Object('-', this));
	}
	//chamber top left 
	else if ((row >= 3 && row < 7) && (col >= 3 && col < 29)){
			content = make_shared<Object>(Object('.', this));
	}
	//chamber bottom left 
	else if ((row >= 15 && row < 22) && (col >= 3 && col < 25)){
        content = make_shared<Object>(Object('.', this));
	}
	//chamber middle one 
	else if ((row >= 10 && row < 13) && ( col >= 38 && col < 50)){
         content = make_shared<Object>(Object('.', this));
	}
	// chamber top right (40, 4) to (62, 5)
	else if ((row >= 3 && row < 5) && (col >= 39 && col < 62)){
         content = make_shared<Object>(Object('.', this));
	}else if ((row== 5) && (col >= 39 && col < 70)){
         content = make_shared<Object>(Object('.', this));
	}else if ((row== 6) && (col >= 39 && col < 73)){
         content = make_shared<Object>(Object('.', this));
	}
	//(62,8) to (7 6,13)
	else if ((row >=7 && row<13) && (col >= 61 && col < 76)){
         content = make_shared<Object>(Object('.', this));
	}
	// chamber bottom right (66,17) to (76, 19)
	else if ((row >= 16 && row < 19) && (col >= 65 && col < 76)){
         content = make_shared<Object>(Object('.', this));
	}
	//(20,38) to (22,76)
	else if ((row >= 19 && row < 22) && (col >= 37 && col < 76)){
         content = make_shared<Object>(Object('.', this));
	}
	else {
		content = make_shared<Object>(Object(' ', this));
	//	cout << "AYYYY WE MDE IT";
	}
}


//Tile::Tile(int row, int col, TextDisplay *td, Object *content): row{row}, col{col}, td{td} {} 

int Tile::getColumn() {
    return col;
}

int Tile::getRow() {
    return row;
}

void Tile:: attach(Tile *o) {
    neighbors.emplace_back(o);
}

shared_ptr<Object>Tile:: getObject() {
    return content;
}

void Tile::changeO(shared_ptr<Object> new_content) {
        content = new_content;
}

Tile *Tile::getneighbor(string d, int neighbor_number) {
    int  neighbor_number_two;
    if (neighbor_number == -1) {
        if (d == "we") {
           neighbor_number_two = 0;
        } else if(d == "nw") {
            neighbor_number_two = 1;
        } else if(d == "no") {
          neighbor_number_two = 2;
        } else if(d == "ne") {
             neighbor_number_two = 3;
        } else if(d == "ea") {
            neighbor_number_two = 4;
        } else if(d == "se") {
            neighbor_number_two = 5;
        } else if(d == "so") {
            neighbor_number_two = 6;
        } else if(d == "sw") {
            neighbor_number_two = 7;
        }
    } else {
        neighbor_number_two = neighbor_number;
    }
    return neighbors[neighbor_number_two];
}










