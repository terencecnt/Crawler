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
    std::shared_ptr<TextDisplay> td; 
    std::shared_ptr<Object>content; 
  public:
    Tile(int row, int col);
    ~Tile() = default;
    std::shared_ptr<Object> getObject(); 
    void attach(Tile *o); 
    int getRow();
    int getColumn();
    void changeO(std::shared_ptr<Object> new_content); 
    //update();
    Tile *getneighbor(std::string d); 
    void swapObject(std::shared_ptr<Tile> t1, std::shared_ptr<Tile> t2); 
    //notifyTD()
};

#endif

