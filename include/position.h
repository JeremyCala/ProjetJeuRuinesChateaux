#ifndef POSITION_H
#define POSITION_H

class position
{
public:
    /* Constructor */
    position();
    position(int x, int y);
    position(const position &pos);

    /* Getter */
    int getX() const;
    int getY() const;

    /* Setter */
    void setX(int x);
    void setY(int y);
    void set(int x, int y);
private:
    int d_x, d_y;
};

#endif // POSITION_H
