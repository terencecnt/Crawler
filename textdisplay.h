#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include <iostream>
#include <vector>
#include "tile.h"

class Tile;

class TextDisplay {
  std::vector<std::vector<char>> display;
  int floor;
 public:
  TextDisplay(std::vector<std::vector<Tile>> &board, int floor);
  ~TextDisplay() = default;
void print();
};

#endif
