#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include <iostream>
#include <vector>
#include "tile.h"
//#include "player.h"
#include "object.h"


class Object;
class Tile;

class TextDisplay {
  std::vector<std::vector<char>> display;
  int floor;
  std::string Race; 
  int HP; 
  int Atk;
  int Def;
  //std::shared_ptr<Object> current;
 public:
  TextDisplay(std::vector<std::vector<Tile>> &board, int floor);
  ~TextDisplay() = default;
  void update(Tile &t);
//  void updatePlayer(std::shared_ptr<Object> newP);
  void print();
 // void changePlayer(std::shared_ptr<Object> newP);

};

#endif
