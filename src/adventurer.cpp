#include "position.h"
#include"adventurer.h"

adventurer::adventurer(int hp, int str, int sword, int armor, bool amulet):
d_hp{hp}, d_str{str}, d_sword{sword}, d_armor{armor}, d_amulet{amulet} {}

int adventurer::getHp() const { return d_hp; }

int adventurer::getStr() const { return d_str; }

int adventurer::getPurse() const { return d_purse; }

int adventurer::getSword() const { return d_sword; }

int adventurer::getArmor() const { return d_armor; }

int adventurer::getX() const { return d_pos.getX(); }
int adventurer::getY() const { return d_pos.getY(); }

bool adventurer::getAmulet() const { return d_amulet; }

void adventurer::reparsword(int coin)
{
  d_sword += coin;
  d_purse -= coin;
}

void adventurer::repararmor(int coin)
{
  d_armor += coin;
  d_purse -= coin;
}

void adventurer::move(int x, int y)
{
  d_pos.moveFrom(x, y);
}

void adventurer::attaqued(int str)
{
  int damage = (3*str)/4;
  d_armor -= damage;
  if(d_armor < 0)
    d_hp -= (d_armor + (str-damage));
  else
    d_hp -= (str - damage);
}
