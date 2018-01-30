#ifndef SHIP_H
#define SHIP_H
#include "../Color.h"
#include "Poly.h"

class Ship{
protected:
    Poly *hero1;
public:
    Ship();
    void Draw(int x, int y);
};

#endif
