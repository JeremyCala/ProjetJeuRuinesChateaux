#include<iostream>
#include"position.h"
#include"adventurer.h"
#include"monster.h"
#include"level.h"

level::level():  d_player{100,10,10,10,false} {}

bool level::initLevel()
{
    
    d_map = "22#6-4#1-4.1-4#1-4.1-4#1-4.1-4#6-22#";
    return true;
}