#include "position.h"
#include"adventurer.h"

adventurer::adventurer(int hp, int str, int sword, int armor, bool amulet): 
d_hp{hp}, d_str{str}, d_sword{sword}, d_armor{armor}, d_amulet{amulet} {}

int adventure::getHp() const { return d_hp; }

int adventure::getStr() const { return d_str; }

int adventure::getPurse() const { return d_sword; }

int adventure::getSword() const { return d_armor; }

int adventure::getArmor() const { return d_purse; }

position adventure::getPos() const { return d_pos; }

bool adventure::getAmulet() const { return d_amulet;}
