#include<iostream>
#include"level.h"

level::level():  d_player{100,10,10,10,false} {}

void level::initLevel()
{
    d_rooms.push_back(room{2,2,5,8});
    d_rooms.push_back(room{20,10,10,8});
    d_rooms.push_back(room{10,20,10,8});
    d_player.move(d_rooms[0].getX(), d_rooms[0].getY()); //place le joueur en haut à gauche de la 1ère room
    d_monsters.push_back(std::make_unique<monster>(10,10,0.9,d_rooms[0].getX()+1,d_rooms[0].getY()+1));
    d_monsters.push_back(std::make_unique<monster>(10,10,0.9,d_rooms[0].getX()+2,d_rooms[0].getY()+3));
    d_monsters.push_back(std::make_unique<blindMonster>(10,10,0.9,d_rooms[0].getX()+1,d_rooms[0].getY()+5));
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