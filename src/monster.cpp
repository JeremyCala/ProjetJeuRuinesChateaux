#include <cmath>
#include <random>
#include <curses.h>
#include <iostream>
#include "position.h"
#include "monster.h"

monster::monster(): d_hp{0}, d_str{0}, d_pSkill{0.0}, d_pos{0,0} {}

monster::monster(int hp, int str, double pSkill, int x, int y):
    d_hp{hp}, d_str{str}, d_pSkill{pSkill}, d_pos{x,y} {}

int monster::getHp() const  { return d_hp; }

int monster::getStrength() const  { return d_str; }

double monster::getPercentSkill() const  { return d_pSkill; }

int monster::getX() const { return d_pos.getX(); }
int monster::getY() const { return d_pos.getY(); }
position monster::getPos() const { return d_pos; }

bool monster::alive() const { return d_hp>0; }

void monster::moveFrom(int x, int y)
{
    d_pos.moveFrom(x,y);
}

void monster::set(const position &p)
{
    d_pos.set(p);
}

void monster::move(int x, int y)
{
    /*Se déplace au hasard d’un case (horizontale, vertical ou diagonal)*/

    position direction[8] = {{-1,1},{-1,0},{-1,-1},{0,-1},
                             {0,1},{1,-1},{1,0},{1,1}} ; //Vecteurs déplacement
    do
    {
        int r = rand()%8;
        position newp = direction[r]; //Position aléatoire
        if(allowedToMove(getX()+newp.getX(),getY()+newp.getY())) //Si le monstre est autorisé à se déplacer
        {
            moveFrom(newp.getX(),newp.getY());
            break;
        }
    } while(true);
}

void monster::attacked(int strength)
{
    /* Le monstre est attaqué par une force strength */
    d_hp -= strength;
}

int monster::attack() const
{
    /* Renvoi la force d'attaque */
    int r = rand()%10<d_pSkill*10 ? 1 : 0; //proba de pSkill
    return d_str*0.9*r;
}

sightMonster::sightMonster(int hp, int str, double pSkill, int x, int y) : 
                           monster{hp,str,pSkill,x,y} {}

bool sightMonster::wallBetween(int x, int y) const
{
    /* Détecte la présence d'un mur entre deux points
    en utilisant l'algorithme de ligne de vue de Bresenham */

    int dx = abs(x - getX());
    int dy = abs(y - getY());
    int sx = (getX() < x) ? 1 : -1;
    int sy = (getY() < y) ? 1 : -1;
    int err = dx - dy;
    int x1 = getX();
    int y1 = getY();

    while (x1 != x || y1 != y) 
    {
        if (mvinch(y1,x1) == '#')
            return true; // Il y a un mur entre les deux points
    
        int e2 = 2 * err;
        if (e2 > -dy) 
        {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }
    return false; // Pas de mur entre les deux points
}

position sightMonster::getNearestCell(int x, int y) const
{
    /* Trouve la case verticale ou horizontale qui se rapproche le plus 
    de la position cible en utilisant l'algorithme de ligne de Bresenham */

    int dx = abs(x - getX());
    int dy = abs(y - getY());
    int x1 = getX();
    int y1 = getY();

    if (dx > dy) {
        if (getX() < x) {
            if (mvinch(y1,x1+1) != '#')
                x1++;
        } else if (getX() > x) {
            if (mvinch(y1,x1-1) != '#')
                x1--;
        }
    } else {
        if (getY() < y) {
            if (mvinch(y1+1,x1) != '#')
                y1++;
        } else if (getY() > y) {
            if (mvinch(y1-1,x1) != '#')
                y1--;
        }
    }
    return {x1,y1};
}

void sightMonster::move(int x, int y)
{
    /* Se déplace d’une case (horizontal ou vertical) vers l’aventurier 
    si celui-ci est à moins de huit cases et qu'il n'y a pas de murs entre lui et l'aventurier
    (ou reste sur l’aventurier s’il est en train de l’attaquer)*/

    if (x == getX() && y == getY())  //Le monstre est sur l'aventurier
        return;
    else
    {
        int dist = sqrt(pow(getX() - x,2) + pow(getY() - y,2)); //distance monstre-aventurier
        if(dist > 8 || wallBetween(x,y))
        do
        {
            int r = (rand()%2 == 0) ? 1: -1;
            if(rand()%2 == 0)
            {
                if(allowedToMove(getX()+ r,getY()))
                {
                    set({getX()+r,getY()}); // le monstre avance
                    break;
                }
            }
            else
            {
                if(allowedToMove(getX(),getY()+r))
                {
                    set({getX(),getY()+r});
                    break;
                }
            }
        } while(true);
        
        else
        {
            position newCell {getNearestCell(x,y)}; //case la plus proche en direction du player
            if(allowedToMove(newCell.getX(),newCell.getY()))
                set(newCell); // se déplace en direction du player
        }
    }
}

bool monster::allowedToMove(int x, int y) const
{
    /* Retourne vrai si le monstre est autorisé à se déplacer sur la case (x,y) */
    return mvinch(y,x) != '#' && mvinch(y,x) != 'M'; //autorisé si case non mur et non monstre
}