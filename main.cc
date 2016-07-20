#include "textdisplay.h"
#include "tile.h"
#include "grid.h"
#include "object.h"
#include <iostream>
using namespace std; 


bool isDirection(string s) {
    bool to_return = true;
    if ((s != "no") &&
        (s != "so") &&
        (s != "ea") &&
        (s != "we") &&
        (s != "ne") &&
        (s != "nw") &&
        (s != "se") &&
        (s != "sw")) {
        to_return = false;
    }
}

int main () {
    Grid g;
//    g.print();
   // Tile t(3,4);
   // Enemy(50, 50, 50, "wtf", 'l',
   // g.gridSpawn(); 
    g.initGold();
    g.initPotion();
    g.initPlayer('h');
    g.initStair();
   // cout << 0 << endl;
    
  //  cout << "1"<< endl;
    g.initEnemy();
  //  cout << "2" << endl;
    g.print();
   // cout << 3 << endl;
    /*
    string to_replay = "q";
    while(true) {
        Grid g;
        string s;
        cout << "Choose a Race: (h)umans, (d)warf, (e)lves, (o)rc" << endl;
        cin >> s;
        if ((s != "d") &&
            (s != "e") &&
            (s != "h") &&
            (s != "o")){
            cout << "This race does not exist. Bye." << end;
        } else {
            initPlayer(s);
        }
        while(true) {
            cin >> s;
            if ((s == "u") || (s == "a")) {
                cin >> s;
                if (!isDirection(s)) {
                    cout << "Direction does not exist" << endl;
                    continue;
                } else {
                    if (s== "u") {
                        g.pickup(s);
                    } else {
                        g.attack(s);
                    }
                }
            } else if(s == "r") {
                to_replay = "replay";
                break;
            } else if(s == "q") {
                to_replay = "surrender";
                break;
            } else if (isDirection(s)) {
                g.move(s);
            } else {
                cout << "Wrong Input" << endl;
                continue;
            }
            to_replay = g.state();
            if((to_return == "lost") || (to_return == "win")) break;
        }
        if (to_replay == "lost") {
            cout << "You lost" << endl;
        } else if (to_replay == "win") {
            cout << "You won" << endl;
        }
        if (to_replay == "surrender") {
            break;
        } else {
            string temp;
            cout << "do you want to play again?(yes/no)" << endl;
            cin >> temp;
            if (temp == "yes") {
                continue;
            } else {
                break;
            }
        }
    }
    */
}
