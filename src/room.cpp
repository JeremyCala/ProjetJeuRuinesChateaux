#include"room.h"

room::room(): d_x{0},d_y{0}, d_length{0}, d_width{0} {}

room::room(int x, int y, int length, int width):
    d_x{x}, d_y{y} , d_length{length}, d_width{width} {}

int room::getX() const {return d_x;}
int room::getY() const {return d_y;}
int room::getLength() const {return d_length;}
int room::getWidth() const {return d_width;}