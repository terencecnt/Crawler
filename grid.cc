#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <math.h> 
#include "grid.h"
#include <iostream>
#include <memory>
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
            if (((i - 1) <= row) && ((j+1) <= column)) {
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
    int size = Board.size();
    for (int i = 0; i < size; ++i) {
        Board.pop_back();
    }
}

void Grid::GridSpawn(){ //CALL THIS WHEN U LEVEL UP 
    cout << "LET ME SPAWN" << endl;
    clearGrid();
    int original_floor = floor;
    shared_ptr<Player> original_player = player;
    cout << "working: 1" << endl;
    Grid::Grid new_grid;
    cout << "working: 2" << endl;
    (*this) = new_grid;
    cout << "working: 3" << endl;
    floor = original_floor + 1;
    cout << "working: 4" << endl;
    char race = original_player->getRace().at(0);
    int currentHP = original_player->getHP();
   int currentGold = original_player->getMyGold();
    cout << "working: 5" << endl;
    initPlayer('H');
    cout << "working: 6" << endl;
    player->changeHP(1000000000000);
    player->changeGold(100000000);

    initStair();
    cout << "working: 7" << endl;
    initGold();
 
    cout << "working: 8" << endl;
    initPotion();
   
    cout << "working: 9" << endl;
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
        row = rand()%25;
        col = rand()%79;
            GoldNum = rand()%8 + 1; 
        if (Board[row][col].getObject()->getKind() == '.') {
            GoldNum = rand()%8 + 1; 
            //cout << GoldNum<< " : it me" << endl;
            if ((1 <= GoldNum) && (GoldNum<= 8)) alive = 1;
            if ((GoldNum >= 1) && (GoldNum <= 5)){
                cout << "Wtf1"<< endl;
                auto temp = make_shared<Normal>(Normal(&Board[row][col]));
                Board[row][col].changeO(temp);
            }
            else  if ((GoldNum == 6) || (GoldNum <= 7)){
                cout << "Wtf2"<< endl;
                auto temp = make_shared<Small>(Small(&Board[row][col]));
                Board[row][col].changeO(temp);
            }

            else if (GoldNum == 8) {
                cout << "Wtf3"<< endl;
                auto temp = make_shared<dragonGold>(dragonGold(&Board[row][col]));
                //spawn new dragon
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
                       // cout << "WTF" << endl;
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
    cout << "String is " << d << endl;
    try {
        auto to_move_to = player->getParent()->getneighbor(d);
        char kind = to_move_to->getObject()->getKind();
        if ((to_move_to == nullptr)||
                ((kind != 'G')&&
                 (kind != '.')&&
                 (kind != '/')&&
                 (kind != '#')&& 
                 (kind != '+' ))) {
            cout << "throwing error" << endl;
                    throw "error";
                } 
        else if (kind == '/') {
           //call gridspawns
            GridSpawn();
           cout <<"NEXT LEVEL, GRID SPAWN " << endl;
           return;
       }

       else if (kind == 'G') { 
           //call getGold;
           int row = player->getParent()->getRow();
           int col = player->getParent()->getColumn();
           cout << "Get gold" << endl;
           auto temp = to_move_to->getObject();
           player->getGold(static_pointer_cast<Treasure>(temp));
           //get rid of the gold
           swapObject(to_move_to, player->getParent());
           Board[row][col].changeO( make_shared<Object>(Object('.', to_move_to)));


       }  
        
        else {
 
                    swapObject(to_move_to, player->getParent());
                }

 enemyMove();
        }
    catch(...) {
        cout << "Unable to move to " << d << endl;
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
   


}

/*
   void Grid:: attack(string s) {
   shared_ptr<Object> enemy = 
   }
*/  


string Grid::state() {
  //  if (player->getHP() == 0) {
    //    return "lost";
//} else
    if (floor == 5) {
        return "win";
    } else {
        return "neutral";
    }
}

void Grid::use(string d) {
    // check if neighbour is a potion
    auto neighbourOfObj = player->getParent()->getneighbor(d);
    auto neighbourObj = neighbourOfObj->getObject();
    if (neighbourObj != nullptr) {
        if (neighbourObj->getKind() == 'P') {
            char type = ((static_pointer_cast<Potion>(neighbourObj))->getType())[0];
           // if (type == 

            td->changeAction("Potion is used");
            player->usePotion(static_pointer_cast<Potion> (neighbourObj));
        } else {
            td->changeAction("Not a Potion");
        }
    } else {
        td->changeAction("Dead End");
    }
}





void Grid::attack(string d) {
    try {
        auto enemy = player->getParent()->getneighbor(d)->getObject(); //object
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
            int pHP = player->getHP();
            int pAtk = player->getAtk();
            int pDef = player->getDef();
           
            //enemy stats 
            int eHP = static_pointer_cast<Character>(enemy)->getHP();
            int eAtk = static_pointer_cast<Character>(enemy)->getAtk();
            int eDef = static_pointer_cast<Character>(enemy)->getDef();

            cout << "man has this much HP: " << eHP << endl;
            cout << "man has this much Atk: " << eAtk << endl;
            cout << "man has this much Def: " << eDef << endl;
          

            //fight

            //player attacks first
            int damage_on_enemy = ceil(100/(100+eDef))*pAtk;

            // subtract hp from enemy
            static_pointer_cast<Character>(enemy)->changeHP(-damage_on_enemy);

            if (eHP == 0){ //check if enemy died.
                int eRow = player->getParent()->getneighbor(d)->getRow(); 
                int eCol = player->getParent()->getneighbor(d)->getColumn(); 

                Board[eRow][eCol] = Tile(eRow,eCol);
                td->update(Board[eRow][eCol]);
                cout << "lol enemy died" << endl;
                return;
            }

            //enemy attacks 
            int damage_on_player = ceil(100/(100+pDef))*eAtk;

            //subtract HP from player
            player->changeHP(-damage_on_player);

            //check if player died.
            if (pHP == 0 ){
                cout << "LOL U ded" << endl;
                return;
            }
        }
    }catch(...) {
        cout << "Not a valid enemy at " << d << endl;
    }
}





































































































void Grid::enemyMove() { 
    srand(time(NULL)); 
    int enemyNum = 0;
    //this section makes enemy attack if there is a nearby player 
    for (int enemyNum =0; enemyNum <20; ++enemyNum) {
        //dont attack if merchant isn't hostile
   //     if (enemies[enemyNum]->getKind() == 'M' && !static_pointer_cast<Merchant>(enemies[enemyNum])->checkHostile()){ 
        for (int i =0 ; i < 8; ++i) {
            if (enemies[enemyNum]->getKind() == 'M'){
                shared_ptr<Merchant> test=  static_pointer_cast<Merchant>(enemies[enemyNum]);
                string hostile = test->checkHostile();
                cout << "HELLO STOP "<< hostile << endl;
                 break;
            }

                else if (enemies[enemyNum]->getParent()->getneighbor("false", i)->getObject()->getKind() == '@') { 
                    cout << "CODE IN ATTACK FROM " << enemies[enemyNum]->getKind() << "TO PLAYER" << endl;
                    break;

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






























































































































































































































































































































































































































































































































































































































































