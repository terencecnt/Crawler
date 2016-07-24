#ifndef _TREASURE_
#define _TREASURE_
#include<memory>
#include "tile.h"
#include "object.h"
#include "enemy.h"

class Treasure : public Object{
	const int value;

public:
	Treasure(int value, Tile* parent);
	~Treasure();
	int getValue();
};


class Normal: public Treasure {
public:
	Normal(Tile* parent);
	~Normal();

};

class Small: public Treasure {
public:
	Small(Tile* parent);
	~Small();

};

class merchantGold: public Treasure {
public:
	merchantGold(Tile* parent);
	~merchantGold();

};

class dragonGold: public Treasure {
    std::shared_ptr<Dragon> owner;
	bool alive;
public:
	dragonGold(Tile* parent);
	~dragonGold();
    void updateDragon(std::shared_ptr<Dragon> father);
    bool isAlive();
    void changeStatus();
};


#endif
