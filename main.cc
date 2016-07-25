#include "textdisplay.h"
#include "tile.h"
#include "grid.h"
#include "object.h"
#include <iostream>
#include<fstream>
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
    return to_return;
}

int main (int argc, char* argv[]) {
    bool input_exist = false;
    ifstream f;

    if (argc > 1) {
        string input = argv[1];
        f.open(input);
        if(f.good()) {
            input_exist = true;
        } else {
            cout << "File Cannot be Found" << endl;
            return 0;
        }
    }

    string to_replay = "q";
    while(true) {
        Grid g;
        string s;
        bool hit_stairs = false;
        cout << "Choose a Race: (h)umans, (d)warf, (e)lves, (o)rc" << endl;
        cin >> s;
        if ((s != "d") &&
            (s != "e") &&
            (s != "h") &&
            (s != "o")){
            cout << "This race does not exist. Bye." << endl;
            break;
        } else {
            g.initGrid(input_exist, s[0], f);
        }
        while(true) {
            g.print();
            cout << "Enter Command" << endl;
            cin >> s;
            string s_two;
            if ((s == "u") || (s == "a")) {
                cin >> s_two;
                if (!isDirection(s_two)) {
                    cout << "Direction does not exist" << endl;
                    continue;
                } else {
                    if (s== "u") {
                        g.use(s_two);
                    } else {
                        g.attack(s_two);
                    }
                }
            } else if(s == "r") {
                to_replay = "replay";
                break;
            } else if(s == "q") {
                to_replay = "surrender";
                break;
            } else if (isDirection(s)) {
                hit_stairs = g.move(s);
            } else {
                cout << "Wrong Input" << endl;
                continue;
            }

            to_replay = g.state();
            if ((to_replay == "neutral") && hit_stairs) {
                g.GridSpawn(input_exist, f);
                to_replay = g.state();

                hit_stairs = false;
            }
            if((to_replay == "lost")|| (to_replay=="win")) break;
        }
        if (to_replay == "lost") {
            cout << "You lost" << endl;
            cout << "Your score is 0." << endl;
        } else if (to_replay == "win") {
            cout << "You won" << endl;
            int score = g.displayScore();
            if (g.getPlayerRace() == "Human") {
                score *= 2;
            }
            cout<< "Your score is " << score << "." << endl;
        }
        if (to_replay == "surrender") {
            cout << "You surrendered" << endl;
            break;
        } else {
            string temp;
            cout << "do you want to play again?(yes/no)" << endl;
            cin >> temp;
            if (temp == "yes" || temp == "y") {
                continue;
            } else {
                break;
            }
        }
    }
}
