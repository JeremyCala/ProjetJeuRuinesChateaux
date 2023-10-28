#include <iostream>

#include"game.h"

game::game(): d_isRunning{true}, d_menu{true}, d_game{false}, d_edit{false}{}

void game::mainLoop()
{
    while(d_isRunning)
    {
        menuLoop();
        gameLoop();
        editLoop();
    }
}

void game::menuLoop()
{
    int choice;

    while(d_menu)
    {
        std::cout<<"1. JOUER\n2. EDITER\n3. QUITTER\n\nVotre choix : ";
        std::cin>>choice;

        switch (choice)
        {
        case 1:
            d_menu = false;
            d_game = true;
            break;
        case 2:
            d_menu = false;
            d_edit = true;
            break;
        case 3:
            std::cout<<"A BIENTOT !!!";
            d_menu = false;
            d_isRunning = false;
            break;

        }
    }
}

void game::gameLoop()
{
    while(d_game)
    {
        d_game = false;
        d_menu = true;
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
