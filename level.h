#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <string>
#include <memory>

class position;
class adventurer;
class monster;

/*
# = exterieur
- = mur
. = rien
*/
using tabMonster = std::vector<std::unique_ptr<monster>>;

class level
{
public:
    /* Constructor */
    level();

    /* Methods */
    bool initLevel();
private:
    std::string d_map;
    adventurer d_player;
    position d_exit;
    position d_amulet;
    tabMonster d_monsters;
};

#endif // LEVEL_H