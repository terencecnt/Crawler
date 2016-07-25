#ifndef __GRID_H__
#define __GRID_H__
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include "textdisplay.h"
#include "player.h"
#include "enemy.h"
#include "treasure.h"

class Player;
class Enemy;

class Grid {
  std::vector<std::vector<Tile>> Board;
  int floor;
  std::shared_ptr<TextDisplay> td;
  std::shared_ptr<Player> player;
  std::vector<std::shared_ptr<Object>> enemies;
    public:
  void initStair();
  void initPlayer(char Race);
  void initEnemy(); 
  void initGold();
  void initPotion();
public:
  Grid();
  ~Grid();
  void clearGrid();
  std::string state(); 
  void print();
  void initGrid(bool has_file, string type);
  void swapObject(Tile *t1, Tile *t2);
  bool move(std::string d);
  void use(std::string d); 
  void attack(std::string d);
  void defend(int d);
  //void pickup(std::string d);
 void enemyMove();
  void GridSpawn();
};

#endif
