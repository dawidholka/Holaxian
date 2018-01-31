#ifndef SHIP_H
#define SHIP_H
#include "../../Color.h"
#include "Poly.h"

class Ship
{
protected:
    iXY Size;
    int Scale;
    Poly MainBody;
    Poly BodyDetail;
public:
    Ship();
    int GetSizeX(){ return Size.x; };
    int GetSizeY(){ return Size.y; };
    void Draw(int x, int y);
    int ResetX();
    int ResetY();
};


#endif
