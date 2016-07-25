#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <math.h> 
#include "grid.h"
#include <iostream>
#include <memory>
#include <string>
#include "character.h"
#include "enemy.h"
#include "player.h"
#include "human.h"
#include "elf.h"
#include "dwarf.h"
#include "orc.h"
using namespace std;

Grid:: Grid() {
    floor = 1;
    int row = 25;
    int column =79;
    for (int i= 0; i < row; ++i) {
        vector<Tile> row;
        for (int j =0; j < column; ++j) {

            row.emplace_back(Tile(i,j));
        }

        Board.emplace_back(row);
    }

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            if (((j - 1) >= 0)) {
                //attach west
                Board[i][j].attach(&Board[i][j-1]);
            } else {
                Board[i][j].attach(nullptr);
            }

            if (((i - 1) >= 0) && ((j - 1) >= 0)) {
                //attach nw
                Board[i][j].attach(&Board[i - 1][j - 1]);
            } else {
                Board[i][j].attach(nullptr);
            }

            if ((i - 1) >= 0) {
                //attach north 
                Board[i][j].attach(&Board[i-1][j]);
            } else {
                Board[i][j].attach(nullptr);
            }
            if (((i - 1) >= 0) && ((j+1) <= column)) {
                //attach ne
                Board[i][j].attach(&Board[i-1][j + 1]);
            } else {
                Board[i][j].attach(nullptr);
            }
            if ((j+1) <= column) {
                //attach ea
                Board[i][j].attach(&Board[i][j + 1]);
            } else {
                Board[i][j].attach(nullptr);
            }
            if (((i + 1) <= row) && ((j+1) <= column)) {
                //attach se
                Board[i][j].attach(&Board[i+1][j + 1]);
            } else {
                Board[i][j].attach(nullptr);
            }
            if ((i + 1) <= row) {
                //attach south
                Board[i][j].attach(&Board[i+1][j]);
            } else {
                Board[i][j].attach(nullptr);
            }
            if (((i + 1) <= row) && ((j-1) >= 0)) {
                //attach sw
                Board[i][j].attach(&Board[i+1][j-1]);
            } else {
                Board[i][j].attach(nullptr);
            }
        }
    }    
    shared_ptr<TextDisplay>theDisplay = make_shared<TextDisplay>(TextDisplay(Board, floor, nullptr));
    td = theDisplay;
}

void Grid::clearGrid(){    
    int row = 25;
    int column =79;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            char kind = Board[i][j].getObject()->getKind();
            if (kind != '.' && kind != '-' && kind != '+' && kind != '|' && kind != '#' && kind != ' '){
                Board[i][j].changeO(make_shared<Object>(Object('.', &Board[i][j])));
                td->update(Board[i][j]);
            }
           
        }
    }
    
    int enemSize = enemies.size();
    for (int i = 0; i < enemSize; ++i) {
        enemies.pop_back();
    }
    
}

void Grid::GridSpawn(){ //CALL THIS WHEN U LEVEL UP 
    char race = player->getRace()[0];
    int currentHP = player->getOriginal("HP");
    int currentGold = player->getMyGold();
    ++floor;
    td->updateFloor(floor);
    td->changeAction("You are now on floor " + to_string(floor));


    clearGrid();

    

    initPlayer(race);
    player->changeHP(currentHP);
    player->changeGold(currentGold);

    initStair();
    initGold();
 
   
    initPotion();
    initEnemy();


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
                row = rand()%25;
                col = rand()%79;
                if ((Board[row][col].getObject()->getKind() == '.') && ((row < 3 || row >= 7) || (col < 3 || col >= 29))){
                    auto temp = make_shared<Object>(Object('/', &Board[row][col]));
                    Board[row][col].changeO(temp);
                    td->update(Board[row][col]);
                    return;
                }
            }

        case 2: // stairs cant spawn in chamber2

            while (true) {
                row = rand()%25;
                col = rand()%79;
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
                row = rand()%25;
                col = rand()%79;
                if ((Board[row][col].getObject()->getKind() == '.') && ((row < 10 || row >= 13) || ( col < 38 || col >= 50))){
                    auto temp = make_shared<Object>(Object('/', &Board[row][col]));
                    Board[row][col].changeO(temp);
                    td->update(Board[row][col]);
                    return;
                }
            }

        case 4: // stairs cant spawn in chamber4

            while (true) {
                row = rand()%25;
                col = rand()%79;
                if ((Board[row][col].getObject()->getKind() == '.') && ((row < 15 || row >= 22) || (col < 4 || col >= 25))){
                    auto temp = make_shared<Object>(Object('/', &Board[row][col]));
                    Board[row][col].changeO(temp);
                    td->update(Board[row][col]);
                    return;
                }
            }

        case 5: // stairs cant spawn in chamber5

            while (true) {
                row = rand()%25;
                col = rand()%79;
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
        row = rand()%25;
        col = rand()%79;
        if (Board[row][col].getObject()->getKind() == '.') {
            shared_ptr<Player>temp;
            if (Race == 'h') {
                temp = make_shared<Player>(Human(&Board[row][col]));
            }

            else if (Race == 'e') {
                temp = make_shared<Player>(Elf(&Board[row][col]));
            }

            else  if (Race == 'd') {
                temp = make_shared<Player>(Dwarf(&Board[row][col]));
            }

            else  if (Race == 'o') {
                temp = make_shared<Player>(Orc(&Board[row][col]));
            }

            else {
                temp = make_shared<Player>(Human(&Board[row][col]));
            }
            //auto temp = make_shared<Object>(Player(&Board[row][col]));
            this->player = temp; // set the Player field
            //td->changePlayer(temp);
            Board[row][col].changeO(temp);
            td->updatePlayer(temp);
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
        row = rand()%25;
        col = rand()%79;
        if (Board[row][col].getObject()->getKind() == '.') {
            shared_ptr<Enemy> temp;
            enemNum = rand()%17 + 1; 
            if ((1 <= enemNum) && (enemNum<= 18)) alive = 1;
            if ((enemNum == 1) || (enemNum == 2)){
                temp = make_shared<Merchant>(Merchant(&Board[row][col]));

            }
            else  if ((enemNum >= 3) && (enemNum <= 5)){
                temp = make_shared<Vampire>(Vampire(&Board[row][col]));
            }

            else if ((enemNum >= 6) && (enemNum <= 9)){
                temp = make_shared<Werewolf>(Werewolf(&Board[row][col]));
            }
            else if ((enemNum >= 10) && (enemNum <= 14)){
                temp = make_shared<Goblin>(Goblin(&Board[row][col]));
            }
            else if ((enemNum == 15) || (enemNum == 16)){
                temp = make_shared<Phoenix>(Phoenix(&Board[row][col]));
            }
            else if ((enemNum == 17) || (enemNum == 18)){
                temp = make_shared<Troll>(Troll(&Board[row][col]));
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
        row = rand()%25;
        col = rand()%79;
        GoldNum = rand()%8 + 1; 
        if (Board[row][col].getObject()->getKind() == '.') {
            GoldNum = rand()%8 + 1; 
            if ((1 <= GoldNum) && (GoldNum<= 8)) alive = 1;
            if ((GoldNum >= 1) && (GoldNum <= 5)){
                auto temp = make_shared<Normal>(Normal(&Board[row][col]));
                Board[row][col].changeO(temp);
            }
            else  if ((GoldNum == 6) || (GoldNum <= 7)){
                auto temp = make_shared<Small>(Small(&Board[row][col]));
                Board[row][col].changeO(temp);
            }

            else if (GoldNum == 8) {
                auto temp = make_shared<dragonGold>(dragonGold(&Board[row][col]));
                int dragon=0;
                while (true){ 
                    dragon = rand()%8; 
                    Tile *dragonTile; 
                    if (dragon == 0){
                        dragonTile = temp->getParent()->getneighbor("we"); 
                    }
                    else if (dragon == 1){
                        dragonTile = temp->getParent()->getneighbor("nw"); 
                    }
                    else if (dragon == 2){
                        dragonTile = temp->getParent()->getneighbor("no"); 
                    }
                    else if (dragon == 3){
                        dragonTile = temp->getParent()->getneighbor("ne"); 
                    }
                    else if (dragon == 4){
                        dragonTile = temp->getParent()->getneighbor("ea"); 
                    }
                    else if (dragon == 5){
                        dragonTile = temp->getParent()->getneighbor("se"); 
                    }
                    else if (dragon == 6){
                        dragonTile = temp->getParent()->getneighbor("so"); 
                    }
                    else if (dragon == 7){
                        dragonTile = temp->getParent()->getneighbor("sw"); 
                    }
                    if (dragonTile->getObject()->getKind() == '.') {
                        auto temp_two = make_shared<Dragon>(Dragon(dragonTile, temp));
                        //int dragon_row = dragonTile->getRow();
                        Board[row][col].changeO(temp);
                        //int dragon_col = dragonTile->getColumn();
                        dragonTile->changeO(temp_two);
                        temp->updateDragon(temp_two);
                        td->update(*dragonTile);
                        break;
                    }
                }
            }
            if (alive == 1) {
                --gold;
                td->update(Board[row][col]);
            }
        }
    }
}




void Grid::initPotion() {
    srand(time(NULL));
    int row; 
    int col; 
    int potion = 0;
    int potionType; // randNum to choose the 6 potions
    int chamber; // randnum to choose form 5 chambers
    while(potion < 10) {
        row = rand()%25;
        col = rand()%79;
        potionType = rand()%6;
        chamber = rand()%5;
        switch (chamber) {

            case 0: // spawn in chamber 1
                if ((Board[row][col].getObject()->getKind() == '.')&&((row >= 3 && row < 7) && (col >= 3 && col < 29))){
                    shared_ptr<Potion> temp;
                    switch (potionType) {
                        case 0: 
                            temp = make_shared<Potion>(RH(&Board[row][col]));
                            break;
                        case 1: 
                            temp = make_shared<Potion>(BA(&Board[row][col]));
                            break;
                        case 2:
                            temp = make_shared<Potion>(BD(&Board[row][col]));
                            break;
                        case 3:  
                            temp = make_shared<Potion>(PH(&Board[row][col]));
                            break;
                        case 4: 
                            temp = make_shared<Potion>(WD(&Board[row][col]));
                            break;
                        case 5: 
                            temp = make_shared<Potion>(WA(&Board[row][col]));
                            break;
                    }
                    Board[row][col].changeO(temp);
                    td->update(Board[row][col]);
                    ++potion;
                    break;
                }
            case 1: // spawn in chamber 2
                if ((Board[row][col].getObject()->getKind() == '.')&& (((row >= 3 && row < 5)&&(col >= 39 && col < 62))
                            ||((row== 5)&&(col >= 39 && col < 70))||((row== 6)&&(col >= 39 && col < 73))||((row >=7 && row<13) && (col >= 61 && col < 76)))){
                    shared_ptr<Potion> temp;
                    switch (potionType) {
                        case 0: 
                            temp = make_shared<Potion>(RH(&Board[row][col]));
                            break;
                        case 1: 
                            temp = make_shared<Potion>(BA(&Board[row][col]));
                            break;
                        case 2:
                            temp = make_shared<Potion>(BD(&Board[row][col]));
                            break;
                        case 3:  
                            temp = make_shared<Potion>(PH(&Board[row][col]));
                            break;
                        case 4: 
                            temp = make_shared<Potion>(WD(&Board[row][col]));
                            break;
                        case 5: 
                            temp = make_shared<Potion>(WA(&Board[row][col]));
                            break;
                    }
                    Board[row][col].changeO(temp);
                    td->update(Board[row][col]);
                    ++potion;
                    break;
                }
            case 2: // spawn in chamber 3
                if ((Board[row][col].getObject()->getKind() == '.')&& ((row >= 10 && row < 13) && (col >= 38 && col < 50))){
                    shared_ptr<Potion> temp;
                    switch (potionType) {
                        case 0: 
                            temp = make_shared<Potion>(RH(&Board[row][col]));
                            break;
                        case 1: 
                            temp = make_shared<Potion>(BA(&Board[row][col]));
                            break;
                        case 2:
                            temp = make_shared<Potion>(BD(&Board[row][col]));
                            break;
                        case 3:  
                            temp = make_shared<Potion>(PH(&Board[row][col]));
                            break;
                        case 4: 
                            temp = make_shared<Potion>(WD(&Board[row][col]));
                            break;
                        case 5: 
                            temp = make_shared<Potion>(WA(&Board[row][col]));
                            break;
                    }
                    Board[row][col].changeO(temp);
                    td->update(Board[row][col]);
                    ++potion;
                    break;
                }
            case 3: // spawn in chamber 4
                if ((Board[row][col].getObject()->getKind() == '.')&& ((row >= 15 && row < 22) && (col >= 4 && col < 25))){
                    shared_ptr<Potion> temp;
                    switch (potionType) {
                        case 0: 
                            temp = make_shared<Potion>(RH(&Board[row][col]));
                            break;
                        case 1: 
                            temp = make_shared<Potion>(BA(&Board[row][col]));
                            break;
                        case 2:
                            temp = make_shared<Potion>(BD(&Board[row][col]));
                            break;
                        case 3:  
                            temp = make_shared<Potion>(PH(&Board[row][col]));
                            break;
                        case 4: 
                            temp = make_shared<Potion>(WD(&Board[row][col]));
                            break;
                        case 5: 
                            temp = make_shared<Potion>(WA(&Board[row][col]));
                            break;
                    }
                    Board[row][col].changeO(temp);
                    td->update(Board[row][col]);
                    ++potion;
                    break;
                }
            case 4: // spawn in chamber 5
                if ((Board[row][col].getObject()->getKind() == '.')&&(((row >=7 && row<13)&&(col >= 61 && col < 76))||((row >= 16 && row < 19)&&(col >= 65 && col < 76))||
                            ((row >= 19 && row < 22)&&(col >= 37&&col < 76)))){
                    shared_ptr<Potion> temp;
                    switch (potionType) {
                        case 0: 
                            temp = make_shared<Potion>(RH(&Board[row][col]));
                            break;
                        case 1: 
                            temp = make_shared<Potion>(BA(&Board[row][col]));
                            break;
                        case 2:
                            temp = make_shared<Potion>(BD(&Board[row][col]));
                            break;
                        case 3:  
                            temp = make_shared<Potion>(PH(&Board[row][col]));
                            break;
                        case 4: 
                            temp = make_shared<Potion>(WD(&Board[row][col]));
                            break;
                        case 5: 
                            temp = make_shared<Potion>(WA(&Board[row][col]));
                            break;
                    }
                    Board[row][col].changeO(temp);
                    td->update(Board[row][col]);
                    ++potion;
                    break;
                }
        }       
    }
}





/*
void Grid::initGrid(bool has_file, char type) {
    if (has_file) {
        vector<Dragon> Dragons;
        vector<dragonGold> Golds;
        int row = 25;
        int col = 79;
        string current;
        shared_ptr<Object> temp;
        for (int i = 0; i < row; ++i) {
            getline(f, current);
            for(int j = 0; j < col; ++j) {
                char cur = current[j];
                switch (cur) {
                    case '0':
                        temp = make_shared<Potion>(RH(&Board[row][col]));
                    case '1':
                        temp = make_shared<Potion>(BA(&Board[row][col]));
                    case '2':
                        temp = make_shared<Potion>(BD(&Board[row][col]));
                    case '3':
                        temp = make_shared<Potion>(PH(&Board[row][col]));
                    case '4':
                        temp = make_shared<Potion>(WA(&Board[row][col]));
                    case '5':
                        temp = make_shared<Potion>(WD(&Board[row][col]));
                    case '6':
                        temp = make_shared<Normal>(Normal(&Board[row][col]));
                    case '7':
                        temp = make_shared<Small>(Small(&Board[row][col]));
                    case '8':
                        temp = make_shared<merchantGold>(merchantGold(&Board[row][col]));
                    case '9':
                        temp = make_shared<dragonGold>(dragonGold(&Board[row][col]));
                        Golds.emplace_back(temp);
                    case 'V':
                        temp = make_shared<Vampire>(Vampire(&Board[row][col]));
                    case 'W':
                        temp = make_shared<Werewolf>(Werewolf(&Board[row][col]));
                    case 'N':
                        temp = make_shared<Goblin>(Goblin(&Board[row][col]));
                    case 'P':
                        temp = make_shared<Phoenix>(Phoenix(&Board[row][col]));
                    case 'T':
                        temp = make_shared<Troll>(Troll(&Board[row][col]));
                    case 'M':
                        temp = make_shared<Merchant>(Merchant(&Board[row][col]));
                    case 'D':
                        temp = make_shared<Dragon>(Dragon(dragonTile, nullptr));
                        Dragons.emplace_back(temp);
                    case '@':
                        switch(type) {
                            case 'h':
                                temp = make_shared<Player>(Human(&Board[row][col]));
                            case 'e':
                                temp = make_shared<Player>(Elf(&Board[row][col]));
                            case 'd':
                                temp = make_shared<Player>(Dwarf(&Board[row][col]));
                            case 'o':
                                temp = make_shared<Player>(Orc(&Board[row][col]));
                        }
                    this->player = temp;
                    td->updatePlayer(temp);
                }
                    Board[row][col].changeO(temp);
                    td->update(Board[row][col]);
            }
        }
    }
}

*/




























































































































































































































































































iiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiii
i

iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiii
i

iiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiii
iiiiiiiiiiiiiiiiiiii
iiiii
iiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiii
i


iiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiii
iiiii
i

iiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiii
iiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiii
i




iiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiii
iiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii

iiiiiiiiiiiii

iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii

iiiiiiiiiiiiiiiiiii

iiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii

iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii


iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiii
iiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii

iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiii
iiiiiiiii
iiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiii
i

iiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiii

iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiii

iiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii

iiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii

iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii

iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii

iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiii
iiiiiiiii
iiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiii
i





































































































iiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiii
iiiiiiiii
iiii
iiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiiiiiiiiiiii
iiiiiiiiiiiii
iiiii
iiiii
iiiiiiiiii






























































































































































































































































































































































































































































































































































































































































