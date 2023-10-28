#ifndef MONSTER_H
#define MONSTER_H

#include "position.h"

class monster
{
public : 

    /*Getter*/
    int lifepoint() const;
    int strenght() const;
    int percentSkill() const;
    position getPosition() const;

    /*Methods*/
    void move(const position& aventurerPosition); 
    void attaqued(int strenght);

private :
    int d_lp, d_str, d_pSkill;
    position d_pos;
};

class blindMonster : public monster
{
public :
    void move();
};

#endif // MONSTER_H