#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "grid.h"
#include <iostream>
#include <string>
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

    int chamber;
    int pRow = player->getParent()->getRow(); //players current location
    int pCol = player->getParent()->getColumn();

    if ((pRow >= 3 && pRow < 7) && (pCol >= 3 && pCol < 29)){ // top left chamber1
        chamber = 1; 
    }
    // top right chamber 2
    else if (((pRow >= 3 && pRow < 5)&&(pCol >= 39 && pCol < 62))||((pRow== 5)&&(pCol >= 39 && pCol < 70))||
        ((pRow== 6)&&(pCol >= 39 && pCol < 73))||((pRow >=7 && pRow<13) && (pCol >= 61 && pCol < 76))) {
        chamber = 2;
    }
    else if ((pRow >= 10 && pRow < 13) && ( pCol >= 38 && pCol < 50)){ // middle chamber 3
        chamber = 3;
    }else if ((pRow >= 15 && pRow < 22) && (pCol >= 4 && pCol < 25)){ // bottem left chamber 4
        chamber = 4;
    }else{ // bottom right chamber 5
        chamber = 5;
    }

    int row;
    int col;
    srand(time(NULL));
    switch (chamber) {
        case 1: // stairs cant spawn in chamber1
    
        while (true) {
            row = rand()%24;
            col = rand()%78;
            if ((Board[row][col].getObject()->getKind() == '.') && ((row < 3 || row >= 7) || (col < 3 || col >= 29))){
                auto temp = make_shared<Object>(Object('/', &Board[row][col]));
                Board[row][col].changeO(temp);
                td->update(Board[row][col]);
                return;
            }
        }

        case 2: // stairs cant spawn in chamber2
   
        while (true) {
            row = rand()%24;
            col = rand()%78;
            if ((Board[row][col].getObject()->getKind() == '.')&& 
            (((row < 3 || row >= 5)||(col < 39 || col >= 62)) && ((row != 5) || (col < 39 || col >= 70))&&
            ((row != 6)||(col < 39 || col >= 73)) && ((row < 7 || row >= 13) ||(col < 61 || col >= 76)))) {
                auto temp = make_shared<Object>(Object('/', &Board[row][col]));
                Board[row][col].changeO(temp);
                td->update(Board[row][col]);
                return;
            }
        }

        case 3: // stairs cant spawn in chamber3

        while (true) {
            row = rand()%24;
            col = rand()%78;
            if ((Board[row][col].getObject()->getKind() == '.') && ((row < 10 || row >= 13) || ( col < 38 || col >= 50))){
                auto temp = make_shared<Object>(Object('/', &Board[row][col]));
                Board[row][col].changeO(temp);
                td->update(Board[row][col]);
                return;
            }
        }
 
        case 4: // stairs cant spawn in chamber4
       
        while (true) {
            row = rand()%24;
            col = rand()%78;
            if ((Board[row][col].getObject()->getKind() == '.') && ((row < 15 || row >= 22) || (col < 4 || col >= 25))){
                auto temp = make_shared<Object>(Object('/', &Board[row][col]));
                Board[row][col].changeO(temp);
                td->update(Board[row][col]);
                return;
            }
        }

        case 5: // stairs cant spawn in chamber5
    
        while (true) {
            row = rand()%24;
            col = rand()%78;
            if ((Board[row][col].getObject()->getKind() == '.') && 
                (((row < 16 || row >= 19) || (col < 65 && col >= 76)) &&((row < 19 || row >= 22)||(col < 37 || col >= 76)))){
                auto temp = make_shared<Object>(Object('/', &Board[row][col]));
                Board[row][col].changeO(temp);
                td->update(Board[row][col]);
                return;
            }
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
            this->player = temp; // set the Player field
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

/*
void Grid::initPotion() {
    srand(time(NULL));
    int PotionNum;
    int row; 
    int col; 
    int potion = 10;
    while(true) {
        if (potion == 0) break;
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
*/

























































































































































void Grid::use(string d) { 
    Tile *a= player->getParent()->getneighbor(d);
    //if tile points to a potion, then use potion 
    player->usePotion(a->getObject());
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




















































































































































































































































































































































































































































































































































































































































