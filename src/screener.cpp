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

void screener::showPlayer(const adventurer &a) const
{
    mvprintw(a.getY(), a.getX(), "@");
}

void screener::showMonsters(const level &l) const
{
    for (int i = 0; i< l.getNbMonsters(); ++i) 
    {
        const auto& currentMonster = l.getMonster(i);
        mvprintw(currentMonster->getY(), currentMonster->getX(),"M");
    }
}

void screener::showStats(const level &l) const
{
    mvprintw(10,d_length + 2,"Hp :"); 
    mvprintw(10,d_length + 7, "%d", l.getPlayer().getHp());

    mvprintw(12,d_length + 2,"Strength :");
    mvprintw(12,d_length + 13, "%d", l.getPlayer().getStrength());

    mvprintw(14,d_length + 2,"Purse :");
    mvprintw(14,d_length + 10, "%d", l.getPlayer().getPurse());

    mvprintw(16,d_length + 2,"Sword :");
    mvprintw(16,d_length + 10, "%d", l.getPlayer().getSword());

    mvprintw(18,d_length + 2,"Armor :");
    mvprintw(18,d_length + 10, "%d", l.getPlayer().getArmor());
}

void screener::showATH(const level &l) const
{
    mvprintw(2,d_length + 4,"A");
    mvprintw(2,d_length + 6,"Z");
    mvprintw(2,d_length + 8,"E");
    mvprintw(4,d_length + 4,"Q");
    mvprintw(4,d_length + 6,"@");
    mvprintw(4,d_length + 8,"D");
    mvprintw(6,d_length + 4,"W");
    mvprintw(6,d_length + 6,"X");
    mvprintw(6,d_length + 8,"C");

    showStats(l);
}

void screener::showLevel(const level &l) const
{
    clear();
    for(int i = 0; i < d_width; ++i)
        for(int j = 0; j < d_length; ++j)
            mvprintw(i,j,"#");
    for(int i = 0;i < l.getNbRooms(); ++i)
        showRoom(l.getRoom(i));
    showATH(l);

    showMonsters(l);
    showPlayer(l.getPlayer());
    
    move(l.getPlayer().getY(),l.getPlayer().getX());
    refresh();    
    noecho();
}



