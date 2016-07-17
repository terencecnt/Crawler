#ifndef __GRID_H__
#define __GRID_H__
#include <iostream>
#include <vector>
#include "textdisplay.h"

class player;

class Grid {
  std::vector<std::vector<Tile>> Board;
  int floor;
  TextDisplay *td;
  Player *player;
  //vector<enemy> enemies;
    public:
  void  initStair();
  void initPlayer();
  void initEnemy(); 
public:
  Grid();
  ~Grid();

  void print();
  void move(string d);

  /*
  void GridSpawn();
*/
};

#endif
