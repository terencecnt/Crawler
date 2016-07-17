#include <iostream>
#include "textdisplay.h"
using namespace std;

TextDisplay::TextDisplay(std::vector<vector<Tile>> &board, int floor): floor{floor} {
    int rows = 25;
    int columns = 79;

    for (int i = 0; i < rows; ++i) {
        vector<char> row;

        for (int j = 0; j < columns; ++j) {
            Object *current = board[i][j].getObject();
            char spot = current->getKind();;
            row.emplace_back(spot);       
 }
//	cout << endl;
        display.emplace_back(row);
    }
}

//patch
TextDisplay:: update(std::vector<vector<Tile>> &board, int floor) { 
    int rows = 25;
    int columns = 79;

    for (int i = 0; i < rows; ++i) {
        vector<char> row;

        for (int j = 0; j < columns; ++j) {
            Object *current = board[i][j].getObject();
            char spot = current->getKind();;
            row.emplace_back(spot);       
 }
//	cout << endl;
        display.emplace_back(row);
    }
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








