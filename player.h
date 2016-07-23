#ifndef _PLAYER_
#define _PLAYER_
#include<memory>
#include<string>
#include "character.h"
#include "potion.h"

class Treasure;
class Character;

class Player: public Character {
    int original_HP;
    int original_ATK;
    int original_DEF;
    int gold; 
    std::string Race;
    public: 
   	Player(int HP, int Atk, int Def, char Kind, Tile *parent); 
    Player(int HP, int Atk, int Def, std::string Race, char Kind, Tile *parent); 
    ~Player() = default; 
    std::string getRace();
    int getMyGold();
    int getOriginal(std::string field = "hp");
    void changeGold(int old_Gold);
    int changeHP(int n, std::string to_change = "increase") override;
    virtual void usePotion(std::shared_ptr<Potion> p);
    virtual void getGold(std::shared_ptr<Treasure> t);
};

#endif
