#ifndef ADVENTURER_H
#define ADVENTURER_H

class position;

class adventurer
{
public:
  adventurer(int hp, int str, int sword, int armor, bool amulet);

  int getHp() const;
  int getStr() const;
  int getPurse() const;
  int getSword() const;
  int getArmor() const;
  position getPos() const;
  bool getAmulet() const;
  void reparsword(int coin);
  void repararmor(int coin);
  void move(position pos);
  void attaqued(int strenght);
private:
  int d_hp, d_str, d_sword, d_armor, d_purse;
  bool d_amulet;
  position d_pos;  
};

#endif // ADVENTURER_H
