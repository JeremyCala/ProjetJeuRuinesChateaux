#include<curses.h>
#include"level.h"
#include"screener.h"

screener::screener(): d_length{0}, d_width{0} {}

screener::screener(int l, int w): d_length{l}, d_width{w} {}

void screener::showMenu() const
{
    clear();
    mvprintw(0,0,"\n1. JOUER\n2. EDITER\n3. QUITTER\n\nVotre choix : ");
    refresh();
}

void screener::showRoom(const room& r) const
{
    for(int i = r.getY(); i < r.getWidth() + r.getY(); ++i)
    {
        for(int j = r.getX(); j < r.getLength() + r.getX(); ++j)
            mvprintw(i,j,".");
    }
}

void screener::showLevel(const level &l) const
{
    clear();
    for(int i = 0; i < d_width; ++i)
        for(int j = 0; j < d_length; ++j)
            mvprintw(i,j,"#");
    for(int i = 0;i < l.getNbRooms(); ++i)
        showRoom(l.getRoom(i));

    mvprintw(l.getPlayer().getY(), l.getPlayer().getX(),"@"); //affiche le joueur

    for (int i = 0; i< l.getNbMonsters(); ++i) //affiche les monstres
    {
        const auto& currentMonster = l.getMonster(i);
        mvprintw(currentMonster->getY(), currentMonster->getX(),"M");
    }
        
    refresh();    

}
