#include <cmath>
#include <random>
#include <curses.h>
#include <iostream>
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

void monster::move(int x, int y)
{
    // se déplace d’une case (horizontal ou vertical) vers l’aventurier 
    // si celui-ci est à moins de huit cases
    // (ou reste sur l’aventurier s’il est en train de l’attaquer)

    int dist = sqrt(pow(d_pos.getX() - x,2) + pow(d_pos.getY() - y,2));
    if(dist > 8)
    do
    {
        int r = (rand()%2 == 0) ? 1: -1;

        if(rand()%2 == 0)
        {
            if(mvinch(d_pos.getY(),d_pos.getX()+ r) == '.')
            {
                d_pos.moveFrom(r,0);
                break;
            }
        }
        else
        {
            if(mvinch(d_pos.getY()+r, d_pos.getX()) == '.')
            {
                 d_pos.moveFrom(0,r);
                 break;
            }
        }
    }
    while(true);
}

void monster::attaqued(int strenght)
{
    d_hp -= strenght;
    if (d_hp<0) d_hp = 0;
}

blindMonster::blindMonster(int hp, int str, double pSkill, int x, int y) : 
                           monster{hp,str,pSkill,x,y} {}

void blindMonster::move(int x, int y)
{
    //se déplace au hasard d’un case (horizontale, vertical ou diagonal)
}