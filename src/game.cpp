#include <iostream>
#include <curses.h>
#include <random>
#include <ctime>
#include"level.h"
#include"game.h"
#include"levelEditor.h"

game::game(): d_isRunning{true}, d_menu{true}, d_game{false}, d_edit{false}, d_createLevel{false}, d_end{false},
              d_gameOver{false}, d_screener{100,30}, d_num_level{1}, d_nb_level{2} {}

void game::mainLoop()
{
    srand(time(0));
    initscr();
    while(d_isRunning)
    {
        if(d_menu) menuLoop();
        else if(d_game) gameLoop();
        else if(d_edit) editLoop();
        else if(d_createLevel) createLevelLoop();
        else if (d_save) saveLoop();
        else if(d_end) endLoop();
        else if(d_gameOver) gameOverLoop();
    }
    endwin();
}

void game::menuLoop()
{
    while(d_menu)
    {
        d_screener.showMenu(d_num_level,d_nb_level);
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
    d_level.initLevel(std::to_string(d_num_level)+".txt");
    
    while(d_game && !d_level.endLevel() &&!d_level.gameOver()) //tant que le niveau n'est pas terminé
    {
        d_screener.showLevel(d_level);
        playerInputGame();
        d_level.moveMonsters();
    }

    if (!d_level.gameOver()) //savoir pourquoi le niveau s'est terminé
        if (++d_num_level>d_nb_level) //passe au niveau suivant ou revient au 1er niveau
        {
            d_num_level=1; 
            d_end = true;
        }
        else
            d_menu = true;   
    else
        d_gameOver = true;
        
    d_game = false;
}

void game::editLoop()
{
    while(d_edit)
    {
        d_screener.showEditMenu();
        char choice = getch();
        switch (choice)
        {
        case '1':
            d_edit = false;
            d_createLevel = true;
            break;
        case '2':
            d_edit = true;
            break;
        case '3':
            d_menu = true;
            d_edit = false;
            break;
        default:
            break;
        }
    }
}

void game::createLevelLoop()
{
    levelEditor newLevel{};
    
    if (newLevel.createLevel(d_screener, d_nb_level+1)) //si le niveau a été créer correctement
    {
        ++d_nb_level; //il y a un niveau en plus
        d_save = true; //on affiche le message de sauvegarde
    }
    else
        d_edit = true;
    d_createLevel = false;
}

void game::saveLoop()
{
    while(d_save)
    {
        d_screener.showSaveSuccess(d_nb_level);
        char choice = getch();
        if (choice == '\n')
        {
            d_edit = true;
            d_save = false;
            break;
        }
    }
}

void game::endLoop()
{
    while(d_end)
    {
        d_screener.showEnd(d_nb_level);
        char choice = getch();
        if (choice == '\n')
        {
            d_menu = true;
            d_end = false;
            break;
        }
    }
}

void game::gameOverLoop()
{
    while(d_gameOver)
    {
        d_screener.showGameOver();
        char choice = getch();
        if (choice == '\n')
        {
            d_menu = true;
            d_gameOver = false;
            break;
        }
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

    case 27:
        d_game = false;
        d_menu= true;
        d_level.clear();
        break;

    default:
        break;
    }
}
