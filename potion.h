#ifndef _POTION_
#define _POTION_
#include "tile.h"
#include "object.h"

class Tile;

class Potion : public Object{
    const int value;
	const std::string type;
  public:
	Potion(const int value, const std::string type, Tile* parent);
	~Potion();
	int getValue();
    std::string getType();
};

class RH: public Potion{
  public:
	RH(Tile* parent);
	~RH();
};

class BA: public Potion{
  public:
	BA(Tile* parent);
	~BA();
};

class BD: public Potion{
  public:
	BD(Tile* parent);
	~BD();
};


class PH: public Potion{
  public:
	PH(Tile* parent);
	~PH();
};
class WD: public Potion{
  public:
	WD(Tile* parent);
	~WD();
};
class WA: public Potion{
  public:
	WA(Tile* parent);
	~WA();
};

#endif
