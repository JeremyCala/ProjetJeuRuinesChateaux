#ifndef SCREENER_H
#define SCREENER_H

class room;
class adventurer;
class level;
class monster;

class screener
{
public:
    /*Constructor*/
    screener();
    screener(int l, int w);

    /*Getters*/
    int length() const;
    int width() const;
    void getCursorPos(int &x, int &y) const;
    char getChar(int x, int y) const;

    /*Methods*/
    void print (int x, int y, const char *c) const;
    void moveCursor(int x, int y) const;
    void blockInput() const;
    void showMenu(int numLevel, int nbLevel) const;
    void showEnd(int nbLevel) const;
    void showGameOver() const;
    void showEditMenu() const;
    void showEditLevel(int nbLevel) const;
    void showEditLevel(const level &l) const;
    void showCreateLevel() const;
    void initCreateLevel() const;
    void showSaveError() const;
    void showSaveSuccess(int numLevel) const;

    /*Game methods*/
    void showRoom(const room& r) const;
    void showPlayer(const adventurer &a) const;
    void showMonsters(const level& l) const;
    void showAmulet(const level &l) const;
    void showExit(const level &l) const;
    void showLevel(const level &l) const;
    void showStats(const level &l) const;
    void showATH(const level &l) const;
    void showMonsterStats(const monster &m) const;
    void showCoins(const level &l) const;
private:
    int d_length, d_width;
};
#endif // SCREENER_H