#include "position.h"
#include "monster.h"


int monster::lifepoint() const  { return d_lp; }

int monster::strenght() const  { return d_str; }

int monster::percentSkill() const  { return d_pSkill; }

position monster::getPosition() const { return d_pos; }

void monster::move(const position& aventurerPosition)
{
    // se déplace d’une case (horizontal ou vertical) vers l’aventurier 
    // si celui-ci est à moins de huit cases
    // (ou reste sur l’aventurier s’il est en train de l’attaquer)
}

void monster::attaqued(int strenght)
{
    d_lp -= strenght;
    if (d_lp<0) d_lp = 0;
}

void blindMonster::move()
{
    //se déplace au hasard d’un case (horizontale, vertical ou diagonal)
}