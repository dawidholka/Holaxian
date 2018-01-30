#ifndef BOSS_H
#define BOSS_H
#include "Poly.h"
#include "../Color.h"

class Boss
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
    Boss();
    int GetSizeX(){ return SizeX; };
    int GetSizeY(){ return SizeY; };
    void Draw(int x, int y);
};


#endif
