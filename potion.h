#ifndef _POTION_
#define _POTION_
#include "tile.h"
#include "object.h"

class Potion : public Object{
	const int value;

public:
	Potion(const int value, Tile* parent);
	~Potion();
	int getValue();
	virtual int getValue() = 0;

};

class RH: public Potion{
public:
	RH(Tile* parent);
	~RH();
	int getValue();
}

class BA: public Potion{
public:
	BA(Tile* parent);
	~BA();
	int getValue();
}

class BD: public Potion{
public:
	BD(Tile* parent);
	~BD();
	int getValue();
}


class PH: public Potion{
public:
	PH(Tile* parent);
	~PH();
	int getValue();

}
class WD: public Potion{
public:
	WD(Tile* parent);
	~WD();
	int getValue();
}
class WA: public Potion{
public:
	WA(Tile* parent);
	~WA();
	int getValue();
}

#endif