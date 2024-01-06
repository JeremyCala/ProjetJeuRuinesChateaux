#include <iostream>
#include <curses.h>
#include <random>
#include <ctime>
#include <filesystem>
#include"level.h"
#include"game.h"
#include"levelEditor.h"

game::game(): d_isRunning{true}, d_menu{true}, d_game{false}, d_edit{false}, d_createLevel{false}, d_end{false},
              d_gameOver{false}, d_editLevel{false}, d_screener{100,30}, d_num_level{1}, d_nb_level{0}
{
    /* On compte le nombre de niveau dans le fichier level pour initialiser le nombre de niveaux */
    
    for (const auto& entry : std::filesystem::directory_iterator("level")) 
        if (std::filesystem::is_regular_file(entry.path())) d_nb_level++;
}

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
        else if(d_editLevel) editLevelLoop();
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
    /* Boucle du jeu */

    d_level.initLevel(std::to_string(d_num_level)+".txt");
    
    while(d_game && !d_level.endLevel() &&!d_level.gameOver()) //tant que le niveau n'est pas terminé
    {
        d_screener.showLevel(d_level);
        playerInputGame();
        d_level.moveMonsters();
    }

    if (d_level.endLevel()) //si le niveau a été réussi
        if (++d_num_level>d_nb_level) //passe au niveau suivant ou revient au 1er niveau
        {
            d_num_level=1; 
            d_end = true;    //fin du jeu
        }
        else
            d_menu = true;   
    else if(d_level.gameOver()) //si le niveau a échoué
        d_gameOver = true;
    
    d_game = false;
}

void game::editLoop()
{
    /* Menu édition */

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
            d_editLevel = true;
            d_edit = false;
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
    /* Création d'un nouveau niveau */

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

void game::editLevelLoop()
{
    /* Menu de choix du niveau à éditer */

    while(d_editLevel)
    {
        d_screener.showEditLevel(d_nb_level);
        char choice = getch();

        if(choice == 27)
        {
            d_editLevel = false;
            d_edit = true;
        }
        else if(choice -'0' > 0 && choice - '0' <= d_nb_level)
            editLevelLoop(choice-'0');
        
    }
}

void game::editLevelLoop(int numLevel)
{
    /* Edition du niveau numLevel */

    levelEditor newLevel{};
    
    if (newLevel.editLevel(d_screener, numLevel)) //si le niveau a été créer correctement
        d_save = true; //on affiche le message de sauvegarde
    else
        d_edit = true;
    d_editLevel = false;
}

void game::saveLoop()
{
    /* Menu de sauvegarde */
    while(d_save)
    {
        d_screener.showSaveSuccess();
        char choice = getch();
        if (choice == '\n') //retour menu
        {
            d_edit = true;
            d_save = false;
            break;
        }
    }
}

void game::endLoop()
{
    /* Menu de fin */

    while(d_end)
    {
        d_screener.showEnd(d_nb_level);
        char choice = getch();
        if (choice == '\n') //retour menu
        {
            d_menu = true;
            d_end = false;
            break;
        }
    }
}

void game::gameOverLoop()
{
    /* Menu game over */

    while(d_gameOver)
    {
        d_screener.showGameOver();
        char choice = getch();
        if (choice == '\n') //retour menu
        {
            d_menu = true;
            d_gameOver = false;
            break;
        }
    }
}

void game::playerInputGame()
{
    /* Mouvements du joueur */

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
        d_menu = true;
        d_level.clear();
        break;

    default:
        break;
    }
}
