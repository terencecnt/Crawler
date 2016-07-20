#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "grid.h"
#include<iostream>
#include<string>
#include "enemy.h"
#include "player.h"
#include "human.h"
#include "elf.h"
#include "dwarf.h"
#include "orc.h"
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

void Grid::initPlayer(char Race) {
    int row;
    int col;
    srand(time(NULL));
    while (true) {
        row = rand()%24;
        col = rand()%78;
        if (Board[row][col].getObject()->getKind() == '.') {
            shared_ptr<Object>temp;
            if (Race == 'h') {
                temp = make_shared<Object>(Human(&Board[row][col]));
            }

            else if (Race == 'e') {
                temp = make_shared<Object>(Elf(&Board[row][col]));
            }

            else  if (Race == 'd') {
                temp = make_shared<Object>(Dwarf(&Board[row][col]));
            }

            else  if (Race == 'o') {
                temp = make_shared<Object>(Orc(&Board[row][col]));
            }

            else {
                temp = make_shared<Object>(Human(&Board[row][col]));
            }
          //auto temp = make_shared<Object>(Player(&Board[row][col]));
            Board[row][col].changeO(temp);
            td->update(Board[row][col]);
            return;
        }
    }
}


void Grid::initEnemy() {
    srand(time(NULL));
    int enemNum;
    int row; 
    int col; 
    int enem = 20;
    while(true) {
        if (enem == 0) break;
        bool alive = 0;
        row = rand()%24;
        col = rand()%78;
        if (Board[row][col].getObject()->getKind() == '.') {
            shared_ptr<Object> temp;
            enemNum = rand()%17 + 1; 
            if ((1 <= enemNum) && (enemNum<= 18)) alive = 1;
            if ((enemNum == 1) || (enemNum == 2)){
                temp = make_shared<Object>(Merchant(&Board[row][col]));

            }
            else  if ((enemNum >= 3) && (enemNum <= 5)){
                temp = make_shared<Object>(Vampire(&Board[row][col]));
            }

            else if ((enemNum >= 6) && (enemNum <= 9)){
                temp = make_shared<Object>(Werewolf(&Board[row][col]));
            }
            else if ((enemNum >= 10) && (enemNum <= 14)){
                temp = make_shared<Object>(Goblin(&Board[row][col]));
            }
            else if ((enemNum == 15) || (enemNum == 16)){
                temp = make_shared<Object>(Phoenix(&Board[row][col]));
            }
            else if ((enemNum == 17) || (enemNum == 18)){
                temp = make_shared<Object>(Troll(&Board[row][col]));
            }
            if (alive == 1) {
                --enem;
                enemies.emplace_back(temp);
                Board[row][col].changeO(temp);
                td->update(Board[row][col]);
            }
        }
    }
    
}


void Grid::initGold() {
    srand(time(NULL));
    int GoldNum;
    int row; 
    int col; 
    int gold = 10;
    while(true) {
        if (gold == 0) break;
        bool alive = 0;
        row = rand()%24;
        col = rand()%78;
        if (Board[row][col].getObject()->getKind() == '.') {
            shared_ptr<Object> temp;
            GoldNum = rand()%7 + 1; 
            if ((1 <= GoldNum) && (GoldNum<= 8)) alive = 1;
            if ((GoldNum >= 1) || (GoldNum <= 5)){
                temp = make_shared<Object>(Normal(&Board[row][col]));
            }
            else  if ((GoldNum == 6) && (GoldNum <= 7)){
                temp = make_shared<Object>(Small(&Board[row][col]));
            }

            else if (GoldNum == 8) {
                temp = make_shared<Object>(Dragon(&Board[row][col]));
            }
            if (alive == 1) {
                --gold;
                Board[row][col].changeO(temp);
                td->update(Board[row][col]);
            }
        }
    }
}


void Grid::initPotion() {
    srand(time(NULL));
    int GoldNum;
    int row; 
    int col; 
    int gold = 10;
    while(true) {
        if (gold == 0) break;
        bool alive = 0;
        row = rand()%24;
        col = rand()%78;
        if (Board[row][col].getObject()->getKind() == '.') {
            shared_ptr<Object> temp;
            GoldNum = rand()%7 + 1; 
            if ((1 <= GoldNum) && (GoldNum<= 8)) alive = 1;
            if ((GoldNum >= 1) || (GoldNum <= 5)){
                temp = make_shared<Object>(Normal(&Board[row][col]));
            }
            else  if ((GoldNum == 6) && (GoldNum <= 7)){
                temp = make_shared<Object>(Small(&Board[row][col]));
            }

            else if (GoldNum == 8) {
                temp = make_shared<Object>(Dragon(&Board[row][col]));
            }
            if (alive == 1) {
                --gold;
                Board[row][col].changeO(temp);
                td->update(Board[row][col]);
            }
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

/* uncomment when getHP is good
string Grid::state() {
    if (player->getHP() == 0) {
        return "lost";
    } else if (floor == 5) {
        return "win";
    } else {
        return "neutral";
    }
}
*/
