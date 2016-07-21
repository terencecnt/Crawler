
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
                temp = make_shared<Object>(dragonHoard(&Board[row][col]));
                //spawn new dragon
                int dragon;
                while (true){ 
                    int dragon = rand()%7; 
                    Tile dragonTile; 
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
                    if (Board[row][col].getObject()->getKind() == '.') {
                        temp = make_shared<Object>(Dragon(dragonTile));
                        return;
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



void Grid::use(string d) {
    // check if neighbour is a potion 
    Object neighbourObj = player->getParent()->getneighbor(d)->getObject();
    if (neighbourObj->getKind()== 'P') { 
        player->usePotion(neighbourObj);
    } 
}







