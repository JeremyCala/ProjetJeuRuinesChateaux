#include"position.h"

position::position(): d_x{0}, d_y{0} {}

position::position(int x, int y): d_x{x}, d_y{y} {}

position::position(const position &pos): d_x{pos.d_x}, d_y{pos.d_y} {}

int position::getX() const {return d_x;}
int position::getY() const {return d_y;}

void position::setX(int x) {d_x = x;}
void position::setY(int y) {d_y = y;}

void position::set(int x, int y) 
{
    d_x = x;
    d_y = y;
}
