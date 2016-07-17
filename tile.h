#ifndef _TILE_
#define _TILE_
#include <vector>
#include "textdisplay.h"
#include "object.h"
#include "tile.h"
#include <string>

class TextDisplay;
class Object;

class Tile {
    int row;
    int col;
    std::vector<Tile *> neighbors;
    TextDisplay *td;
    Object *content;
  public:
    Tile(int row, int col);
  // Tile(int row, int col, TextDisplay *td, Object *content);
    ~Tile() = default;
    Object *getObject();
    void attach(Tile *o);
    int getRow();
    int getColumn();
    void changeO(Object *new_content);
    //update();
    void getneighbor(string d);
    void swapObject(Tile *t1, Tile*t2);
    //notifyTD()
};

#endif

