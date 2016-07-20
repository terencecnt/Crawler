#ifndef __GRID_H__
#define __GRID_H__
#include<iostream>
#include<vector>
#include<memory>
#include<string>
#include"textdisplay.h"
#include "player.h"
#include "enemy.h"

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
public:
  Grid();
  ~Grid();
  std::string state(); 
  void print();
  void swapObject(Tile *t1, Tile *t2);
  void move(std::string d);
  void use(char d);
  //void pickup(std::string d);

  /*
  void GridSpawn();
*/
};

#endif
