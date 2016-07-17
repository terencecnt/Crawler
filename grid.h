#ifndef __GRID_H__
#define __GRID_H__
#include <iostream>
#include <vector>
#include "textdisplay.h"

class Grid {
  std::vector<std::vector<Tile>> Board;
  int floor;
  TextDisplay *td;
  //vector<enemy> enemies;
    public:
  void  initStair();
 public:
  Grid();
  ~Grid();

  void print();

  /*
  void GridSpawn();
*/
};

#endif
