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
	virtual char getType() = 0;

};

class RH: public Potion{
	const char type;
public:
	RH(Tile* parent);
	~RH();
	char getType();
};

class BA: public Potion{
	const char type;
public:
	BA(Tile* parent);
	~BA();
	char getType();
};

class BD: public Potion{
	const char type;
public:
	BD(Tile* parent);
	~BD();
	char getType();
};


class PH: public Potion{
	const char type;
public:
	PH(Tile* parent);
	~PH();
	char getType();

};
class WD: public Potion{
	const char type;
public:
	WD(Tile* parent);
	~WD();
	char getType();
};
class WA: public Potion{
	const char type;
public:
	WA(Tile* parent);
	~WA();
	char getType();
};

#endif
