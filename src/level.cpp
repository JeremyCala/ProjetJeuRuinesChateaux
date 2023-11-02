#include<iostream>
#include<curses.h>
#include"level.h"

level::level():  d_player{100,10,10,20,false} {}

void level::initLevel()
{
    d_rooms.push_back(room{10,5,40,20});
    d_player.move(d_rooms[0].getX(), d_rooms[0].getY()); //place le joueur en haut à gauche de la 1ère room
    d_monsters.push_back(std::make_unique<monster>(10,10,0.9,d_rooms[0].getX()+1,d_rooms[0].getY()+1));
    d_monsters.push_back(std::make_unique<monster>(10,10,0.9,d_rooms[0].getX()+2,d_rooms[0].getY()+3));
    d_monsters.push_back(std::make_unique<blindMonster>(10,10,0.9,d_rooms[0].getX()+1,d_rooms[0].getY()+5));
     d_monsters.push_back(std::make_unique<monster>(10,10,0.9,d_rooms[0].getX()+20,d_rooms[0].getY()+10));
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

//getposmonster

position level::getposAmulet() const 
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
    
    default:
        break;
    }
}

void level::moveMonsters()
{
    for(auto &m: d_monsters)
    {
        m->move(d_player.getX(),d_player.getY());
    }
}