#include <random>
#include "position.h"
#include "adventurer.h"

adventurer::adventurer(int hp, int str, int sword, int armor):
d_hp{hp}, d_str{str}, d_sword{sword}, d_armor{armor} {}

adventurer::adventurer():
d_hp{0}, d_str{0}, d_sword{0}, d_armor{0} {}

int adventurer::getHp() const { return d_hp; }

int adventurer::getStrength() const { return d_str; }

int adventurer::getPurse() const { return d_purse; }

int adventurer::getSword() const { return d_sword; }

int adventurer::getArmor() const { return d_armor; }

int adventurer::getX() const { return d_pos.getX(); }
int adventurer::getY() const { return d_pos.getY(); }

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

void adventurer::setPos(int x, int y)
{
  d_pos.set(x, y);
}

void adventurer::attacked(int strength)
{
  int damage = (3*strength)/4;
  d_armor -= damage/2;
  if(d_armor < 0)
  {
    int remains = -d_armor;
    d_hp -= (strength/4+remains);
    d_armor = 0;
  }
  else
    d_hp -= (strength/4);
  if (d_hp<0) d_hp=0;
}

int adventurer::attack() const
{
  /*Renvoi la force d'attaque*/
  int r = rand()%10<8 ? 1 : 0; //proba de 80%
  return (d_str + d_sword) * 0.9 * r;
}

void adventurer::kill(int strength)
{
  /* L'aventurier tue le monstre de points de force strength*/
  d_str += (1/4)*strength;
  d_hp += (3/4)*strength;
}

void adventurer::loseSword()
{
  if (d_sword>0)
    d_sword--;
}