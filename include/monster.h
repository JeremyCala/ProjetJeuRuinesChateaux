#ifndef MONSTER_H
#define MONSTER_H

class position;

class monster
{
public : 
    /* Constructor */
    monster();
    monster(int hp, int str, double pSkill, int x, int y);

    /*Getter*/
    int lifepoint() const;
    int strenght() const;
    int percentSkill() const;
    int getX() const;
    int getY() const;

    /*Methods*/
    void move(const position& adventurerPosition); 
    void attaqued(int strenght);

private :
    int d_hp, d_str;
    double d_pSkill;
    position d_pos;
};

class blindMonster : public monster
{
public :
    blindMonster(int hp, int str, double pSkill, int x, int y);
    void move();
};

#endif // MONSTER_H