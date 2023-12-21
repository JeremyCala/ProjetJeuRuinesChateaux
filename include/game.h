#ifndef GAME_H
#define GAME_H

#include"screener.h"
#include"level.h"

class game
{
public:
    game();
    void mainLoop();
private:
    void menuLoop();
    void gameLoop();
    void editLoop();
    void createLevelLoop();
    void editLevelLoop();
    void editLevelLoop(int numLevel);
    void saveLoop();
    void endLoop();
    void gameOverLoop();
    void playerInputGame();
    

    bool d_isRunning, d_menu, d_game, d_edit, d_end, d_gameOver,
     d_save, d_createLevel, d_editLevel;
    screener d_screener;
    level d_level;
    int d_num_level, d_nb_level;
};

#endif // GAME_H
