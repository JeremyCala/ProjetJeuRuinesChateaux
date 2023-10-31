#ifndef SCREENER_H
#define SCREENER_H

class room;
class level;

class screener
{
public:
    screener();
    screener(int l, int w);

    void showMenu() const;
    void showRoom(const room& r) const;
    void showLevel(const level &l) const;
private:
    int d_length, d_width;
};
#endif // SCREENER_H