#include <iostream>
#include <curses.h>
#include"level.h"
#include"game.h"

game::game(): d_isRunning{true}, d_menu{true}, d_game{false}, d_edit{false}, d_screener{100,50} {}

void game::mainLoop()
{
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
    level l;
    l.initLevel();
    
    while(d_game)
    {
        d_screener.showLevel(l);
        char choice = getch();
        switch(choice)
        {
        case '3':
        d_game = false;
        d_menu= true;
        break;
        }
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
