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
    ++floor;
    char race = player->getRace()[0];
    int currentHP = player->getHP();
    int currentGold = player->getMyGold();
    td->updateFloor(floor);
    td->changeAction("You are now on floor " + to_string(floor));


    clearGrid();

    

    initPlayer(race);
    int change = player->getHP() - currentHP;
    player->changeHP(change, "decrease");
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

    int row = pRow + 1;
    int col = pCol;
    auto temp = make_shared<Object>(Object('/', &Board[row][col]));
    Board[row][col].changeO(temp);
    td->update(Board[row][col]);
    return;

    /*
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
    */
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

bool Grid:: move(string d) {
    string output = "Player moved " + d;
    int row = player->getParent()->getRow();
    int col = player->getParent()->getColumn();
    try {
        auto to_move_to = player->getParent()->getneighbor(d);
        char kind = to_move_to->getObject()->getKind();
        if ((to_move_to == nullptr)||
                ((kind != 'G')&&
                 (kind != '.')&&
                 (kind != '/')&&
                 (kind != '#')&& 
                 (kind != '+' ))) {
            //  cout << "throwing error" << endl;
            throw "error";
        } else if (kind == '/') {
            return true;
        } else if (kind == 'G') { 
            //call getGold;
            if (static_pointer_cast<Treasure>(to_move_to->getObject())->getValue() == 6 && static_pointer_cast<dragonGold>(to_move_to->getObject())->isAlive()) {
                cout << "Must slay dragon before retrieving!" << endl;
                return false;
            }
            auto temp = to_move_to->getObject();
            player->getGold(static_pointer_cast<Treasure>(temp));
            swapObject(to_move_to, player->getParent());
            Board[row][col].changeO( make_shared<Object>(Object('.', to_move_to)));
        } else {
            // (kind == '#' || kind == '+') {
            auto newObj = Tile(row, col).getObject();
            swapObject(to_move_to, player->getParent());
            Board[row][col].changeO(newObj);
        }
        enemyMove();
    }
    catch(char const *error) {
        cerr << "Unable to move to " << d << endl;
    }
    td->update(*player->getParent());
    td->update(*player->getParent()->getneighbor("we"));
    td->update(*player->getParent()->getneighbor("nw"));
    td->update(*player->getParent()->getneighbor("no"));
    td->update(*player->getParent()->getneighbor("ne"));
    td->update(*player->getParent()->getneighbor("ea"));
    td->update(*player->getParent()->getneighbor("se"));
    td->update(*player->getParent()->getneighbor("so"));
    td->update(*player->getParent()->getneighbor("sw")); 
    return false;
}


string Grid::state() {
    if (player->getHP() == 0) {
        return "lost";
    } else {
        if (floor == 6) {
            return "win";
        } else {
            return "neutral";
        }
    }
}

void Grid::use(string d) {
    Tile *the_Tile = player->getParent();
    Tile *neighbourOfObj = the_Tile->getneighbor(d);
    auto neighbourObj = neighbourOfObj->getObject();
    if (neighbourObj != nullptr) {
        if (neighbourObj->getKind() == 'P') {
            string type = (static_pointer_cast<Potion>(neighbourObj))->getType();
            string to_return;
            int to_change = (static_pointer_cast<Potion>(neighbourObj))->getValue();
            if (type == "HI") {
                int changed = player->changeHP(to_change);
                to_return = to_string(abs(changed)) + " HP is restored";
            } else if (type == "AI") {
                player->changeATK(to_change);
                to_return = to_string(abs(to_change)) + " attack is restored";
            } else if (type == "DI") {
                player->changeDEF(to_change);
                to_return = to_string(abs(to_change)) + " defense is increased";
            } else if (type == "Hl") {
                int changed = player->changeHP(to_change, "decrease");
                to_return = to_string(abs(to_change)) + " HP is lost";
            } else if(type == "Al") {
                player->changeATK(to_change);
                to_return = to_string(abs(to_change)) + " attack is decreased";
            } else if (type == "Dl") {
                player->changeDEF(to_change);
                to_return = to_string(abs(to_change)) + " defense is decreased";
            }
            shared_ptr<Object>  updated_object = make_shared<Object> (Object('.', neighbourOfObj));
            neighbourOfObj->changeO(updated_object);
            td->update(*neighbourOfObj);
            td->changeAction("Potion is used " + to_return);
        } else {
            td->changeAction("Not a Potion");
        }
    } else {
        td->changeAction("Dead End");
    }
}




void Grid::attack(string d) {
    int row = player->getParent()->getRow();
    int col = player->getParent()->getColumn();
    try {
        shared_ptr<Object> enemy;
        enemy = player->getParent()->getneighbor(d)->getObject(); //object
        char kind = enemy->getKind(); 
     
        if ((enemy == nullptr)||
                ((kind != 'V')&&
                 (kind != 'M')&&
                 (kind != 'W')&&
                 (kind != 'N')&& 
                 (kind != 'X')&&
                 (kind != 'D')&& 
                 (kind != 'T' ))) {
                    throw "error";
        }else{
            if (kind == 'M') { 
                for (int i =0; i <8; ++i) { 
                    if (enemies[i]->getKind()== 'M') { 
                        cout << "Merchants will now be hostile" << endl;
                        static_pointer_cast<Merchant>(enemies[i])->makeHostile();
                    }
                }
            }
            //player stats
            //double pHP = player->getHP();
            double pAtk = player->getAtk();
            //double pDef = player->getDef();
           
            //enemy stats 
            if (static_pointer_cast<Character>(enemy) == nullptr){
                cout << "nullptr" << endl;

            }

            double eHP = (static_pointer_cast<Character>(enemy))->getHP();
            //double eAtk = (static_pointer_cast<Character>(enemy))->getAtk();
            double eDef = (static_pointer_cast<Character>(enemy))->getDef();

            //fight

            //player attacks 
            
            double damage_on_enemy = (100/(100+eDef))*pAtk;

            // subtract hp from enemy
           //cout << "about to deal " << damage_on_enemy << " dmg" << endl;
            
            static_pointer_cast<Character>(enemy)->changeHP(-damage_on_enemy);
            string msg = "You dealt " + to_string(damage_on_enemy) + " dmg to the enemy, it has " + to_string(eHP)+ "HP remaining";
            td->changeAction(msg);


            if (eHP <= 0){ //check if enemy died.
                //check if enemy was a dragon 
                int eRow = player->getParent()->getneighbor(d)->getRow(); 
                int eCol = player->getParent()->getneighbor(d)->getColumn(); 
                if (kind == 'D') { 
                    static_pointer_cast<Dragon>(enemy)->notifyGold();
                    Board[eRow][eCol] = Tile(eRow,eCol);
    
                }
                else if (kind == 'M') { 
                    shared_ptr<merchantGold> merchGold =  make_shared<merchantGold>(merchantGold(enemy->getParent()));
                    enemy->getParent()->changeO(merchGold);
                    //drop merchant gold 
                }
                else { 
                    player->changeGold(player->getMyGold() +1);

                    Board[eRow][eCol] = Tile(eRow,eCol);

                }
                //td->update(Board[row][col]);
                Board[eRow][eCol] = Tile(eRow,eCol);
                td->update(Board[eRow][eCol]);
                td->changeAction("Enemy has died");
                return;
            }
        }
    }catch(char const *error) {
        cerr << "Not a valid enemy at " << d << endl;
    }
}

void Grid::defend(int d) {
    cout << "DEFEND IS CALLED" << endl;
    if (player->getHP()<= 0) { 
        state();
    }
    try {
        shared_ptr<Object> enemy;
        enemy = player->getParent()->getneighbor("false", d)->getObject(); //object
        char kind = enemy->getKind(); 
     
        if ((enemy == nullptr)||
                ((kind != 'V')&&
                 (kind != 'M')&&
                 (kind != 'W')&&
                 (kind != 'N')&& 
                 (kind != 'X')&&
                 (kind != 'D')&& 
                 (kind != 'T' ))) {
                    throw "error";
        }else{

            //player stats
            double pHP = player->getHP();
            //double pAtk = player->getAtk();
            double pDef = player->getDef();
           
            //enemy stats 
            //double eHP = static_pointer_cast<Character>(enemy)->getHP();
            double eAtk = static_pointer_cast<Character>(enemy)->getAtk();
            //double eDef = static_pointer_cast<Character>(enemy)->getDef();
           

            //fight 
            //enemy attacks with 50% chance to miss
            
            double damage_on_player = ceil(100/(100+pDef))*eAtk;

            bool miss = (rand() % 100) < 50;
            if (miss) {
                td->changeAction("Enemy missed attack");
                return;
            }
            string msg= "Enemy dealt " + to_string(damage_on_player) + " damage on you";
            td->changeAction(msg);
            player->changeHP(-damage_on_player);
            //subtract HP from player
            //check if player died.
            if (pHP <= 0 ){
                td->changeAction("You have died");
                return;
            }
        }
    }catch(char const *error) {
        cerr << "Not a valid enemy at " << d << endl;
    }
}





































































































void Grid::enemyMove() { 
    srand(time(NULL)); 
    //int enemyNum = 0;
    //this section makes enemy attack if there is a nearby player 
    for (int enemyNum =0; enemyNum <20; ++enemyNum) {
        //dont attack if merchant isn't hostile
   //     if (enemies[enemyNum]->getKind() == 'M' && !static_pointer_cast<Merchant>(enemies[enemyNum])->checkHostile()){ 
        for (int i =0 ; i < 8; ++i) {
                         if (enemies[enemyNum]->getParent()->getneighbor("false", i)->getObject()->getKind() == '@') { 
            //        cout << "secondEn" << endl;
                //defend(int)a
                     if (enemies[enemyNum]->getKind() == 'M' && not static_pointer_cast<Merchant>(enemies[enemyNum])->checkHostile()){
                         cout << "A friendly Merchant appeared"  << endl;
                     }
                     if (enemies[enemyNum]->getKind() == 'M' &&  static_pointer_cast<Merchant>(enemies[enemyNum])->checkHostile()){
                         cout << "Merchant is angry"  << endl;
                     }
                     else if (i <= 3) { 
                        defend(i+ 4);
                    }
                    else { 
                        defend(i-4);
                    }
               //     cout << "CODE IN ATTACK FROM " << enemies[enemyNum]->getKind() << "TO PLAYER" << endl;
               //     break;
              //      cout << "thirdEn" << endl;
                }
        }
    
    while (true) { 
            int neighbourNum = rand()%8;
            if (enemies[enemyNum]->getParent()->getneighbor("false", neighbourNum)->getObject()->getKind() == '.') { 
                auto to_move_to = enemies[enemyNum]->getParent()->getneighbor("false", neighbourNum);
                swapObject(to_move_to, enemies[enemyNum]->getParent());
                td->update(*enemies[enemyNum]->getParent());
                td->update(*enemies[enemyNum]->getParent()->getneighbor("we"));
                td->update(*enemies[enemyNum]->getParent()->getneighbor("nw"));
                td->update(*enemies[enemyNum]->getParent()->getneighbor("no"));
                td->update(*enemies[enemyNum]->getParent()->getneighbor("ne"));
                td->update(*enemies[enemyNum]->getParent()->getneighbor("ea"));
                td->update(*enemies[enemyNum]->getParent()->getneighbor("se"));
                td->update(*enemies[enemyNum]->getParent()->getneighbor("so"));
                td->update(*enemies[enemyNum]->getParent()->getneighbor("sw"));
                break;
            }
    }
    }
}// break;






























































































































































































































































































































































































































































































































































































































































