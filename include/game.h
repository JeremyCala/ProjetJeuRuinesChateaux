#ifndef GAME_H
#define GAME_H

#include"screener.h"

class game
{
public:
    game();
    void mainLoop();
private:
    void menuLoop();
    void gameLoop();
    void editLoop();

    bool d_isRunning, d_menu, d_game, d_edit;
    screener d_screener;
};

#endif // GAME_H
