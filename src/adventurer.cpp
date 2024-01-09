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

void adventurer::repairSword()
{
  /* Répare l'épée grâce à la bourse */
  d_sword += d_purse;
  d_purse = 0;
}

void adventurer::repairArmor()
{
  /* Répare l'armure grâce à la bourse */
  d_armor += d_purse;
  d_purse = 0;
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
  /* L'aventurier est attaqué par une force strength */

  int damage = (3*strength)/4; // L'armure encaisse 3/4 des dégats
  d_armor -= damage/2;
  if(d_armor < 0)
  {
    repairArmor();
    if (d_armor < 0)  //Si ça ne suffit pas
    {
      int remains = -d_armor;
      d_hp -= (strength/4+remains); //Le reste est encaissé par l'aventurier
      d_armor = 0;
    }
  }
  else
    d_hp -= (strength/4); //L'aventurier encaisse 1/4 des dégats
  if (d_hp<0) d_hp=0;
}

int adventurer::attack()
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
  /* L'aventurier utilise son épée */

  if (d_sword>0)
    d_sword--;
  else
    repairSword(); // répare l'épée
}

void adventurer::increasePurse(int coins)
{
  /* L'aventurier ramasse un tas de "coins" pièces et répare son armure et son épée si possible*/
  if (d_sword == 0)
    d_sword+=coins;
  else if (d_armor == 0)
    d_armor+=coins;
  else
    d_purse+=coins;
}