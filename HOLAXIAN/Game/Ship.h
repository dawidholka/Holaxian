#ifndef SHIP_H
#define SHIP_H
#include "../Color.h"
#include "Poly.h"

class Ship
{
protected:
    int SizeX;
    int SizeY;
    int Scale;
    Poly MainBody;
    Poly BodyDetail;
public:
    Ship();
    int GetSizeX(){ return SizeX; };
    int GetSizeY(){ return SizeY; };
    void Draw(int x, int y);
};


#endif
