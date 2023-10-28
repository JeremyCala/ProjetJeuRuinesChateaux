#ifndef ADVENTURER_H
#define ADVENTURER_H

class adventurer
{
public:
  adventurer(int lp, int str, int sword, int armor);
  int lifepoint() const;
  int strength() const;
  int purse() const;
  int ps_sword() const;
  int ps_armor() const;
  position getposition() const;
  bool amulette() const;
private:
  int d_lp, d_str, ps_sword, ps-armor, d_purse;
  position d_pos;  
};

#endif // ADVENTURER_H
