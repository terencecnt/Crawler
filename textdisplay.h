#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include <iostream>
#include <vector>
#include<memory>
#include "tile.h"

class Tile;
class Player;

class TextDisplay {
  std::vector<std::vector<char>> display;
  int floor;
  std::shared_ptr<Player> current;
  std::string action;
 public:
  TextDisplay(std::vector<std::vector<Tile>> &board, int floor, std::shared_ptr<Player> player, std::string action = "You entered the dungeon");
  ~TextDisplay() = default;
  void update(Tile &t);
  void updateFloor(int floor);
  void changeAction(std::string newAction);
  void updatePlayer(std::shared_ptr<Player> newP);
  void print();
 // void changePlayer(std::shared_ptr<Object> newP);

};

#endif
