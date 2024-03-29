#ifndef ADVENTURER_H
#define ADVENTURER_H

class position;

class adventurer
{
public:
  /* Constructor */
  adventurer();
  adventurer(int hp, int str, int sword, int armor);

  /* Getters */
  int getHp() const;
  int getStrength() const;
  int getPurse() const;
  int getSword() const;
  int getArmor() const;
  int getX() const;
  int getY() const;

  /* Methods */
  void repairSword();
  void repairArmor();
  void move(int x, int y);
  void setPos(int x, int y);
  void attacked(int strength);
  int attack();
  void kill(int strength);
  void loseSword();
  void increasePurse(int coins);

private:
  int d_hp, d_str, d_sword, d_armor, d_purse = 0;
  position d_pos;
};

#endif // ADVENTURER_H