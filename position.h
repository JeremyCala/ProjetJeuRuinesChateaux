#ifndef POSITION_H
#define POSITION_H

class position
{
public:
    position();
    position(int x, int y);
    position(const position &pos);

    int getX() const;
    int getY() const;

    void setX(int x);
    void setY(int y);
private:
    int d_x, d_y;
};

#endif // POSITION_H
