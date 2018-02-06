#ifndef ALIEN_H
#define ALIEN_H
#include "Poly.h"
#include "../../Header.h"

class Alien
{
protected:
    iXY Size;
    int Scale;
    int BodyColor;
    Poly MainBody;
    Poly BodyDetail1;
    Poly BodyDetail2;
public:
    Alien();
    int GetSizeX(){ return Size.x; };
    int GetSizeY(){ return Size.y; };
    void Draw(int x, int y);
};


#endif
