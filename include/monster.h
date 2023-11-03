#ifndef MONSTER_H
#define MONSTER_H

class position;

class monster
{   /* Blind Monsters */

public : 
    /* Constructor */
    monster();
    monster(int hp, int str, double pSkill, int x, int y);

    /*Getter*/
    int getHp() const;
    int getStrength() const;
    int getPercentSkill() const;
    int getX() const;
    int getY() const;

    /*Methods*/
    bool alive() const;
    void moveFrom(int x, int y);
    void set(const position &p);
    void updatePosition(const position &oldPos, const position &newPos);
    virtual void move(int x, int y); 
    void attacked(int strength);
    int attack() const;

private :
    int d_hp, d_str;
    double d_pSkill;
    position d_pos;
};

class sightMonster : public monster
{
public :
    sightMonster(int hp, int str, double pSkill, int x, int y);
    bool wallBetween(int x, int y) const;
    position getNearestCell(int x, int y) const;
    void move(int x, int y) override;
};

#endif // MONSTER_H