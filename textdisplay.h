#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include <iostream>
#include <vector>
#include "tile.h"

class Tile;
class Player;

class TextDisplay {
  std::vector<std::vector<char>> display;
  int floor;
  std::string Race; 
  int HP; 
  int Atk;
  int Def;
  std::shared_ptr<Player> current;
 public:
  TextDisplay(std::vector<std::vector<Tile>> &board, int floor);
  ~TextDisplay() = default;
  void update(Tile &t);
//  void updatePlayer(std::shared_ptr<Object> newP);
  void print();
 // void changePlayer(std::shared_ptr<Object> newP);

};

#endif
