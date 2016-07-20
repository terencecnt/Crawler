#ifndef _TREASURE_
#define _TREASURE_
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
	Dragon* owner;
	bool dead;
public:
	dragonGold(Tile* parent, Dragon* dragon);
	~dragonGold();
	
};


#endif
