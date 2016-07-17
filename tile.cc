#include "grid.h"
#include "tile.h"
using namespace std;

Tile::Tile(int row, int col): row{row}, col{col} {
	if (((col == 0 || col == 78) && (row <= 24)) || ((col == 2) && (((row >= 2) && (row <= 7)) || ((row >= 14) && (row <= 22)))) || (((col == 29) || (col == 38)) && (((row== 2) || (row == 3)) || ((row >= 5) && (row <= 7)))) || ((col == 25) && (((row >= 14) && (row <= 19)) || ((row == 21) || (row == 22)))) || ((col == 36) && (((row >= 18) && (row <= 19)) || ((row == 21) || (row == 22)))) || (((col == 37) || (col == 50)) && ((row >= 9) && (row <= 13))) || ((col == 60) && (((row >= 7) && (row <= 10)) || ((row == 12) || (row == 13)))) || ((col == 62) && (((row >= 2) && (row <= 4))))|| ((col == 64) && (((row >= 15) && (row <= 18)))) || ((col == 70) && ((row == 4) || (row == 5))) || ((col == 73) && ((row == 5) || (row == 6))) || ((col == 76)  && ((((row >= 6) && (row <= 13)))|| ((row >= 15) && (row <= 22))))) { 
		content = new Object('|', this);
	}

	else if ((row== 0) || (row == 24)) {
		content = new Object('-', this);
	}

	else if (((row==7 ) && (col == 13)) || ((row ==14 ) && (col ==13)) || ((row == 29) && (col == 4)) || ((row == 38) && (col == 4)) || ((row == 43) && (col == 7))  || ((row == 43) && (col == 13))  || ((row ==43 ) && (col ==18 )) || ((row ==60 ) && (col ==11 )) || ((row == 69) && (col ==13)) || ((row ==69 ) && (col ==15)) || ((row ==25) && (col ==20)) || ((row ==36) && (col ==20))) {
		content = new Object('+', this);
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
		content = new Object('#', this);
	}

	//horizontal wallz
	else if ((row== 2) &&  ((col >= 3 && col <29) || (col >= 39 && col <62))) {
			content = new Object('-' , this);
	}else if ((row==4) &&  (col >= 63 && col <70)){
			content = new Object('-' , this);
	}else if ((row==5) && (col >= 71 && col <73)){
			content = new Object('-' , this);
	}else if (row==6){
		if (col >= 74 && col <76){
			content = new Object('-' , this);
		}	
	}else if (row== 7){
		if (col >= 3 && col <13){
			content = new Object('-' , this);
		}
		if (col >= 14 && col <29){
			content = new Object('-' , this);
		}
		if (col >= 39 && col < 43 ){
			content = new Object('-' , this);
		}
		if (col >= 44 && col < 60){
			content = new Object('-' , this);
		}
	}else if (row== 9){
		if (col == 38 && col < 43){
			content = new Object('-' , this);
		}	
		if (col == 44 && col < 50){
			content = new Object('-' , this);
		}	
	}else if (row== 13){
		if (col >= 38 && col < 50 && col != 43){
			content = new Object('-' , this);
		}
		if (col >= 62 && col < 76 && col != 69){
			content = new Object('-' , this);
		}	
	}else if (row== 14){
		if (col >= 4 && col <25 && col != 13){
			content = new Object('-' , this);
		}
	}else if (row== 15){
		if( col >= 65 && col <76 && col != 69){
			content = new Object('-' , this);
		}
	}else if (row== 18){
		if (col >= 37 && col <64 && col != 43){
			content = new Object('-' , this);
		}
	}else if (row== 22){
		if(col >= 4 && col <25){
			content = new Object('-' , this);
		}
		if (col >= 37 && col <76){
			content = new Object('-' , this);
		}
	}
	//chamber top left 
	else if (row >= 3 && row < 29){
		if (col >= 3 && col < 7){
			content = new Object('.' , this);
		}
	}
	//chamber bottom left 
	else if (row >= 15 && row < 22){
		if (col >= 4 && col < 25){
			content = new Object('.' , this);
		}
	}
	//chamber middle one 
	else if (row >= 10 && row < 13){
		if ( col >= 12 && col < 50){
			content = new Object('.' , this);
		}
	}
	// chamber top right (40, 4) to (62, 5)
	else if (row >= 3 && row < 5){
		if (col >= 39 && col < 62){
			content = new Object('.' , this);
		}
	}else if (row== 5){
		if(col >= 39 && col < 70){
			content = new Object('.' , this);
		}
	}else if (row== 6){
		if (col >= 39 && col < 73){
			content = new Object('.' , this);
		}
	}
	//(62,8) to (76,13)
	else if (row >=7 && row<13){
		if (col >= 61 && col < 76){
			content = new Object('.' , this);
		}
	}
	// chamber bottom right (66,17) to (76, 19)
	else if (row >= 16 && row < 19){
		if (col >= 65 && col < 76){
			content = new Object('.' , this);
		}
	}
	//(20,38) to (22,76)
	else if (row >= 19 && row < 22){
		if (col >= 37 && col < 76){
			content = new Object('.' , this);
		}
	}

	else {
		content = new Object(' ', this);
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

Object *Tile:: getObject() {
    return content;
}

