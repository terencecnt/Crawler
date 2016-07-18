#include "potion.h"
#include <iostream>
#include <string>
using namespace std;


Potion::Potion(const int value, Tile* parent): Object('P' , parent) , value(value) {}
Potion::~Potion(){}
int Potion::getValue() { return value; }



//Restore Health - restore up to 10 health, cannot exceed max
RH::RH(Tile* parent): Potion(10 , parent), type('H') {}
RH::~RH() {}
char RH::getType() { return type; }



//Boost Attack - increase attack by 5
BA::BA(Tile* parent): Potion(5 , parent), type('A') {}
BA::~BA() {}
char BA::getType() { return type; }


//Boost Defence - increase defence by 5
BD::BD(Tile* parent): Potion(5 , parent), type('D') {}
BD::~BD() {}
char BD::getType() { return type; }


//Posion Health - lose up to 10 health, cannot go below 0
PH::PH(Tile* parent): Potion(-10, parent), type('H') {}
PH::~PH() {}
char PH::getType() { return type; }


//Wound Attack - decrease attack by 5
WA::WA(Tile* parent): Potion(-5, parent), type('A') {}
WA::~WA() {}
char WA::getType() { return type; }


//Wound Defence - decrease defence by 5
WD::WD(Tile* parent): Potion(-5, parent), type('D') {}
WD::~WD() {}
char WD::getType() { return type; }











