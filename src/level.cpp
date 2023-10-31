#include<iostream>
#include"level.h"

level::level():  d_player{100,10,10,10,false} {}

void level::initLevel()
{
    d_rooms.push_back(room{2,2,5,8});
    d_rooms.push_back(room{20,10,10,8});
    d_rooms.push_back(room{10,30,10,8});
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
