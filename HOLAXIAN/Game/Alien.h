#ifndef ALIEN_H
#define ALIEN_H
#include "Poly.h"
#include "../Color.h"

class Alien
{
protected:
    int SizeX;
    int SizeY;
    int Scale;
    int BodyColor;
    Poly MainBody;
    Poly BodyDetail1;
    Poly BodyDetail2;
public:
    Alien();
    int GetSizeX(){ return SizeX; };
    int GetSizeY(){ return SizeY; };
    void Draw(int x, int y);
};


#endif
