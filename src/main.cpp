#include <iostream>
#include "game.h"


// Commande compilation : g++ -I include -L lib src/*.cpp -o test -lpdcurses

int main()
{
    game g;
    g.mainLoop();
    return 0;
}
