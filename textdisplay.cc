#include <iostream>
#include "textdisplay.h"
using namespace std;

TextDisplay::TextDisplay(std::vector<vector<Tile>> &board, int floor): floor{floor} {
    int rows = 25;
    int columns = 79;

    for (int i = 0; i < rows; ++i) {
        vector<char> row;

        for (int j = 0; j < columns; ++j) {
            auto current = board[i][j].getObject();
            char spot = current->getKind();;
            row.emplace_back(spot);       
 }
//	cout << endl;
        display.emplace_back(row);
    }
}

//patch
void TextDisplay:: update(Tile &t) { 
    char temp = (t.getObject())->getKind();
    int row = t.getRow();
    int column = t.getColumn();
    display[row][column] = temp;
}

void TextDisplay::print() {
    int rows = 25;
    int columns = 79;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            cout << display[i][j];
        }
        cout << endl;
    }
}








