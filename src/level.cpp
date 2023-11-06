#include<iostream>
#include<curses.h>
#include"level.h"

level::level():  d_player{100,10,10,20}, d_amulet{false} {}

void level::initLevel()
{
    d_rooms.push_back(room{10,5,40,20});
    d_player.move(d_rooms[0].getX(), d_rooms[0].getY()); //place le joueur en haut à gauche de la 1ère room
    d_monsters.push_back(std::make_unique<sightMonster>(50,10,0.9,d_rooms[0].getX()+3,d_rooms[0].getY()+3));
    d_monsters.push_back(std::make_unique<sightMonster>(50,10,0.9,d_rooms[0].getX()+2,d_rooms[0].getY()+3));
    d_monsters.push_back(std::make_unique<monster>(20,10,0.9,d_rooms[0].getX()+1,d_rooms[0].getY()+5));
    //d_monsters.push_back(std::make_unique<monster>(10,10,0.9,d_rooms[0].getX()+20,d_rooms[0].getY()+10));
}

adventurer level::getPlayer() const
{
    return d_player;
}

int level::getNbRooms() const
{
    return d_rooms.size();
}

room level::getRoom(int n) const
{
    return d_rooms[n];
}

int level::getNbMonsters() const
{
    return d_monsters.size();
}

const std::unique_ptr<monster>& level::getMonster(int n) const
{
    return d_monsters[n];
}

position level::getposAmulet() const 
{
    return d_posAmulet;
}

bool level::getAmulet() const 
{
    return d_amulet;
}

position level::getposExit() const
{
    return d_exit;
}


void level::moveAdventurer(int x, int y)
{
    switch (mvinch(d_player.getY() + y, d_player.getX() + x))
    {
    case '.':
    case 'M':
        d_player.move(x,y);
        break;

    case 'A':
        d_amulet = true;
        d_player.move(x,y);
        break;

    case 'O':
        d_player.move(x,y);
        if (d_amulet == true)
            std::cout<<"waf";
        break;

    
    default:
        break;
    }
}

void level::monsterPlayerFight(tabMonster::iterator& m) 
{
    /* Gère les interactions de combat entre les monstres et le player */

    if ((*m)->getX() == d_player.getX() && (*m)->getY() == d_player.getY())
    {
        d_player.attacked((*m)->attack());
        (*m)->attacked(d_player.attack());
        d_player.loseSword();

        if (!(*m)->alive()) 
        {
            d_player.kill((*m)->getStrength());
            m = d_monsters.erase(m);
        } 
        else
            ++m;
    } 
    else 
        ++m;
}

void level::moveMonsters()
{   
    /* Gère les déplacements des monstres ainsi que les combats */

    for(auto monsterIterator = d_monsters.begin(); monsterIterator != d_monsters.end();)
    {
        (*monsterIterator)->move(d_player.getX(),d_player.getY());
        monsterPlayerFight(monsterIterator);
    }
}