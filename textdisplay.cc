#include <iostream>
#include "textdisplay.h"
#include "player.h"
using namespace std;

TextDisplay::TextDisplay(std::vector<vector<Tile>> &board, int floor, shared_ptr<Player>player, string action): floor{floor}, current{player}, action{action} {
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
     //   current = nullptr;
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



void TextDisplay:: updatePlayer(shared_ptr<Player> newP) { 
    current = newP;
}

void TextDisplay:: updateFloor(int floor){
    this->floor = floor;
}

void TextDisplay::changeAction(string newAction) {
    action += newAction;
}

void TextDisplay::newAction() {
    action = "";
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
//lower part
    cout << "Race: " << current->getRace(); 
    cout << " Gold: " << current->getMyGold();
    int line1 = 14 + (current->getRace()).length();
    cout << string(68 - line1 , ' ') << "Floor: " << floor  <<  endl;
    cout << "HP: " << current->getHP() << endl;
    cout << "Atk: " << current->getAtk() << endl;
    cout << "Def: "  << current->getDef() << endl; 
    cout << "Action: " << action << endl; 
}


/*void changePlayer(shared_ptr<Object> newP) { 
   current =newP;
}*/





