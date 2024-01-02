#include<curses.h>
#include"level.h"
#include"screener.h"
#include"monster.h"

screener::screener(): d_length{0}, d_width{0} {}

screener::screener(int l, int w): d_length{l}, d_width{w} {}

int screener::length() const
{
    return d_length;
}

int screener::width() const
{
    return d_width;
}

void screener::getCursorPos(int &x, int &y) const
{
    /* Retourne la position du curseur dans x et y */
    getyx(stdscr, y, x);
}

char screener::getChar(int x, int y) const
{
    /* Retourne le charactère à la position (x,y) */
    return mvinch(y, x);
}

void screener::print(int x, int y, const char *c) const
{
    mvprintw(y,x,c);
}

void screener::moveCursor(int x, int y) const
{
    move(y,x);
}

void screener::blockInput() const
{
    noecho();
}

void screener::showMenu(int numLevel, int nbLevel) const
{
    clear();
    mvprintw(0,0,"MENU\n\n1. JOUER (Niveau\n2. EDITER\n3. QUITTER");
    mvprintw(2,17, "%d", numLevel);
    mvprintw(2,18, "/");
    mvprintw(2,19, "%d", nbLevel);
    mvprintw(2,20, ")");
    mvprintw(6,0,"Votre choix : ");
    refresh();
}

void screener::showEnd(int nbLevel) const
{
    clear();
    mvprintw(0,0,"\nBravo vous etes parvenu a bout des   niveaux !!!");
    mvprintw(1,35, "%d", nbLevel);
    mvprintw(2,0,"Appuyez sur entree pour revenir au menu");
    refresh();
}

void screener::showGameOver() const
{
    clear();
    mvprintw(0,0,"\nVous avez perdu !\nAppuyez sur entree pour revenir au menu");
    refresh();
}

void screener::showEditMenu() const
{
    clear();
    mvprintw(0,0,"EDITER\n\n1. Creer un nouveau niveau\n2. Editer un niveau actuel\n3. Retour menu");
    mvprintw(6,0,"Votre choix : ");
    refresh();
}

void screener::showEditLevel(int nbLevel) const
{
    clear();
    mvprintw(0,0,"EDITER UN NIVEAU EXISTANT\n\n(echap) Retour");

    int i{1};
    for(i; i <= nbLevel; ++i)
        mvprintw(i+3,0,"%d. Niveau %d", i, i);

    mvprintw(i+6,0,"Votre choix : ");
    refresh();
}

void screener::showEditLevel(const level &l) const
{
    clear();
    for(int i = 0; i < d_width; ++i)
        for(int j = 0; j < d_length; ++j)
            mvprintw(i,j,"#");
    for(int i = 0;i < l.getNbRooms(); ++i)
        showRoom(l.getRoom(i));


    showMonsters(l);
    showAmulet(l);
    showExit(l);
    showPlayer(l.getPlayer());
    
    move(l.getPlayer().getY(),l.getPlayer().getX());
    refresh();    
    noecho();
}

void screener::showCreateLevel() const
{
    mvprintw(1,d_length + 1,"CREER UN NIVEAU");
    mvprintw(3,d_length + 1,"Se deplacer : ");
    mvprintw(5,d_length + 8,"Z");
    mvprintw(6,d_length + 6,"Q");
    mvprintw(6,d_length + 10,"D");
    mvprintw(7,d_length + 8,"X");
    mvprintw(9,d_length + 1,"@ : aventurier");
    mvprintw(10,d_length + 1,"S : monstre voyant");
    mvprintw(11,d_length + 1,"M : monstre aveugle");
    mvprintw(12,d_length + 1,". : sol");
    mvprintw(13,d_length + 1,"# : mur");
    mvprintw(14,d_length + 1,"A : amulette");
    mvprintw(15,d_length + 1,"E : sortie");
    mvprintw(16,d_length + 1,"(Note : pour @ et #");
    mvprintw(17,d_length + 1,"utiliser ALTGR)");
    mvprintw(19,d_length + 1,"Sauvegarder niveau:");
    mvprintw(20,d_length + 4,"Entree");
    mvprintw(22,d_length + 1,"Retour menu :");
    mvprintw(23,d_length + 5,"Echap");
    refresh();
}

void screener::initCreateLevel() const
{
    clear();
    for(int i = 0; i < d_width; ++i)
        for(int j = 0; j < d_length; ++j)
            mvprintw(i,j,"#");
}

void screener::showSaveError() const
{
    mvprintw(25,d_length + 1,"Erreur sauvegarde :");
    mvprintw(26,d_length + 1,"plusieurs ou aucun");
    mvprintw(27,d_length + 1,"@, A ou E");
    refresh();
}

void screener::showSaveSuccess(int numLevel) const
{
    /* Affiche le message de sauvegarde réussie */
    clear();
    mvprintw(1,0,"LE NIVEAU NUMERO   A BIEN ETE SAUVEGARDE !");
    mvprintw(1,17, "%d", numLevel);
    mvprintw(3,0,"Appuyez sur entree pour revenir au menu editer");
    refresh();
}


void screener::showRoom(const room& r) const
{
    for(int i = r.getY(); i < r.getWidth() + r.getY(); ++i)
        for(int j = r.getX(); j < r.getLength() + r.getX(); ++j)
            mvprintw(i,j,".");
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

void screener::showAmulet(const level &l) const
{
    if (!l.getAmulet())
    {
        mvprintw(l.getposAmulet().getY(), l.getposAmulet().getX(), "A");
    }
}

void screener::showExit(const level &l) const
{
    mvprintw(l.getposExit().getY(), l.getposExit().getX(), "E");
}

void screener::showStats(const level &l) const
{
    mvprintw(15,d_length + 1,"STATS AVENTURIER :"); 

    mvprintw(17,d_length + 2,"Hp :"); 
    mvprintw(17,d_length + 7, "%d", l.getPlayer().getHp());

    mvprintw(18,d_length + 2,"Strength :");
    mvprintw(18,d_length + 13, "%d", l.getPlayer().getStrength());

    mvprintw(19,d_length + 2,"Purse :");
    mvprintw(19,d_length + 10, "%d", l.getPlayer().getPurse());

    mvprintw(20,d_length + 2,"Sword :");
    mvprintw(20,d_length + 10, "%d", l.getPlayer().getSword());

    mvprintw(21,d_length + 2,"Armor :");
    mvprintw(21,d_length + 10, "%d", l.getPlayer().getArmor());

    if (l.getAmulet())
        mvprintw(22,d_length + 2,"Amulette : Oui");
    else
        mvprintw(22,d_length + 2,"Amulette : Non");

}

void screener::showATH(const level &l) const
{
    mvprintw(3,d_length + 1,"EXPLORATION");
    mvprintw(6,d_length + 1,"Quitter : echap");
    mvprintw(9,d_length + 4,"A");
    mvprintw(9,d_length + 6,"Z");
    mvprintw(9,d_length + 8,"E");
    mvprintw(11,d_length + 4,"Q");
    mvprintw(11,d_length + 6,"@");
    mvprintw(11,d_length + 8,"D");
    mvprintw(13,d_length + 4,"W");
    mvprintw(13,d_length + 6,"X");
    mvprintw(13,d_length + 8,"C");

    showStats(l);
}

void screener::showMonsterStats(const monster &m) const
{
    mvprintw(24,d_length + 1,"STATS MONSTRE :");

    mvprintw(26,d_length + 2,"Hp :");
    mvprintw(26,d_length + 7, "%d", m.getHp());

    mvprintw(27,d_length + 2,"Strength :");
    mvprintw(27,d_length + 13, "%d", m.getStrength());   

    int habilete = (m.getPercentSkill()*100);
    mvprintw(28,d_length + 2,"Habilete :  %.0f%%", m.getPercentSkill()*100);
}

void screener::showLevel(const level &l) const
{
    clear();
    for(int i = 0; i < d_width; ++i)
        for(int j = 0; j < d_length; ++j)
            mvprintw(i,j,"#");
    for(int i = 0;i < l.getNbRooms(); ++i)
        showRoom(l.getRoom(i));


    showMonsters(l);
    showAmulet(l);
    showATH(l);
    showExit(l);
    showPlayer(l.getPlayer());

    std::unique_ptr<monster> closestMonster = l.getClosestMonster();
    if (closestMonster) //si un monstre est proche
        showMonsterStats(*closestMonster);
    
    move(l.getPlayer().getY(),l.getPlayer().getX());
    refresh();    
    noecho();
}



