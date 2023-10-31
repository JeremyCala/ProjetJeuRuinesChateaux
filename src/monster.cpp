#include "position.h"
#include "monster.h"

monster::monster(): d_hp{0}, d_str{0}, d_pSkill{0.0}, d_pos{0,0} {}

monster::monster(int hp, int str, double pSkill, int x, int y):
    d_hp{hp}, d_str{str}, d_pSkill{pSkill}, d_pos{x,y} {}

int monster::lifepoint() const  { return d_hp; }

int monster::strenght() const  { return d_str; }

int monster::percentSkill() const  { return d_pSkill; }

int monster::getX() const { return d_pos.getX(); }
int monster::getY() const { return d_pos.getY(); }

void monster::move(const position& adventurerPosition)
{
    // se déplace d’une case (horizontal ou vertical) vers l’aventurier 
    // si celui-ci est à moins de huit cases
    // (ou reste sur l’aventurier s’il est en train de l’attaquer)
}

void monster::attaqued(int strenght)
{
    d_hp -= strenght;
    if (d_hp<0) d_hp = 0;
}

blindMonster::blindMonster(int hp, int str, double pSkill, int x, int y) : 
                           monster{hp,str,pSkill,x,y} {}

void blindMonster::move()
{
    //se déplace au hasard d’un case (horizontale, vertical ou diagonal)
}