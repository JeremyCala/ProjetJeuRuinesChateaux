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

    void playerInputGame();

    bool d_isRunning, d_menu, d_game, d_edit;
    screener d_screener;
    level d_level;
};

#endif // GAME_H
