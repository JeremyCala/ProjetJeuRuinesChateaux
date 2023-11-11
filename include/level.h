#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <memory>

#include"position.h"
#include"adventurer.h"
#include"monster.h"
#include"room.h"


using tabMonster = std::vector<std::unique_ptr<monster>>;
using tabRoom = std::vector<room>;

class level
{
public:
    /* Constructor */
    level();

    /* Getters */
    adventurer getPlayer() const;
    int getNbRooms() const;
    room getRoom(int n) const;
    int getNbMonsters() const;
    const std::unique_ptr<monster>& getMonster(int n) const;
    position getposAmulet() const;
    bool getAmulet() const;
    position getposExit() const;

    /* Methods */
    void initLevel();
    void moveAdventurer(int x, int y);
    void updateMonsterPosition(const position &oldPos, const position &newPos);
    void monsterPlayerFight(tabMonster::iterator& monsterIterator);
    void moveMonsters();
    std::unique_ptr<monster> getClosestMonster() const;

private:
    adventurer d_player;
    position d_exit;
    position d_posAmulet;
    bool d_amulet;
    tabMonster d_monsters;
    tabRoom d_rooms;

};

#endif // LEVEL_H
