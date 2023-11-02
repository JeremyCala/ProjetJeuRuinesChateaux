#ifndef SCREENER_H
#define SCREENER_H

class room;
class adventurer;
class level;

class screener
{
public:
    screener();
    screener(int l, int w);

    void showMenu() const;
    void showRoom(const room& r) const;
    void showPlayer(const adventurer &a) const;
    void showMonsters(const level& l) const;
    void showLevel(const level &l) const;
    void showATH() const;
private:
    int d_length, d_width;
};
#endif // SCREENER_H