#ifndef GAME_H
#define GAME_H

class game
{
public:
    game();
    void mainLoop();
    void menuLoop();
    void gameLoop();
    void editLoop();
private:
    bool d_isRunning, d_menu, d_game, d_edit;
};
#endif // GAME_H
