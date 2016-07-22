#include "potion.h"
#include <iostream>
#include <string>
using namespace std;


Potion::Potion(const int value, const string type, Tile* parent): Object('P' , parent) , value(value), type(type) {}
Potion::~Potion(){}
int Potion::getValue() {return value;}
string Potion::getType() {return type;}

//Restore Health - restore up to 10 health, cannot exceed max
RH::RH(Tile* parent): Potion(10 ,"HI", parent) {}
RH::~RH() {}

//Boost Attack - increase attack by 5
BA::BA(Tile* parent): Potion(5 ,"AI", parent){}
BA::~BA() {}

//Boost Defence - increase defence by 5
BD::BD(Tile* parent): Potion(5 , "DI", parent) {}
BD::~BD() {}

//Posion Health - lose up to 10 health, cannot go below 0
PH::PH(Tile* parent): Potion(-10,"Hl" ,parent) {}
PH::~PH() {}

//Wound Attack - decrease attack by 5
WA::WA(Tile* parent): Potion(-5,"Al",parent){}
WA::~WA() {}

//Wound Defence - decrease defence by 5
WD::WD(Tile* parent): Potion(-5, "Dl",parent){}
WD::~WD() {}
