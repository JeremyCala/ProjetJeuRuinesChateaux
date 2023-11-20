#include <iostream>
#include <curses.h>
#include <random>
#include <ctime>
#include"level.h"
#include"game.h"

game::game(): d_isRunning{true}, d_menu{true}, d_game{false}, d_edit{false}, d_screener{100,50} {}

void game::mainLoop()
{
    srand(time(0));
    initscr();
    while(d_isRunning)
    {
        if(d_menu) menuLoop();
        else if(d_game) gameLoop();
        else if(d_edit) editLoop();
    }
    endwin();
}

void game::menuLoop()
{
    while(d_menu)
    {
        d_screener.showMenu();
        char choice = getch();
        switch (choice)
        {
        case '1':
            d_menu = false;
            d_game = true;
            break;
        case '2':
            d_menu = false;
            d_edit = true;
            break;
        case '3':
            d_menu = false;
            d_isRunning = false;
            break;
        default:
            break;
        }
    }
}

void game::gameLoop()
{
    d_level.initLevel("1.txt");
    
    while(d_game)
    {
        d_screener.showLevel(d_level);
        playerInputGame();
        d_level.moveMonsters();
    }
}

void game::editLoop()
{
    while(d_edit)
    {
        d_edit = false;
        d_menu = true;
    }
}

void game::playerInputGame()
{
    char choice = getch();
    switch(choice)
    {
    case 'z':
        d_level.moveAdventurer(0,-1);
        break;
    case 'q':
        d_level.moveAdventurer(-1,0);
        break;
    case 'd':
        d_level.moveAdventurer(1,0);
        break;
    case 'x':
        d_level.moveAdventurer(0,1);
        break;
    case 'a':
        d_level.moveAdventurer(-1,-1);
        break;
    case 'e':
        d_level.moveAdventurer(1,-1);
        break;
    case 'w':
        d_level.moveAdventurer(-1,1);
        break;
    case 'c':
        d_level.moveAdventurer(1,1);
        break;

    case '3':
        d_game = false;
        d_menu= true;
        d_level.clear();
        break;

    default:
        break;
    }
}
