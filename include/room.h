#ifndef ROOM_H
#define ROOM_h

class room
{
public:
    /* Constructors */
    room();
    room(int x, int y, int length, int width);

    /* Getters*/
    int getX() const;
    int getY() const;
    int getLength() const;
    int getWidth() const;
private:
    int d_x, d_y, d_length, d_width;
};

#endif // ROOM_H