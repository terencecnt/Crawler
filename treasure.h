#ifndef _TREASURE_
#define _TREASURE_
#include "tile.h"
#include "object.h"

class Treasure : public Object{
	const int value;

public:
	Treasure::Treasure(const int value, Tile* parent);
	~Treasure();
	virtual int getValue()=0;
};


class Normal: public Treasure {
public:
	Normal(Tile* parent);
	~Normal();
	int getValue();
}

class Small: public Treasure {
public:
	Small(Tile* parent);
	~Small();
	int getValue();
}

class merchantGold: public Treasure {
public:
	merchantGold(Tile* parent);
	~merchantGold();
	int getValue();
}

class dragonGold: public Treasure {
	*Dragon owner;
	bool dead;
public:
	dragonGold(Tile* parent, Dragon* dragon);
	~dragonGold();
	int getValue();
}