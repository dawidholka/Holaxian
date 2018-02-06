#ifndef BOSS_H
#define BOSS_H
#include "Poly.h"
#include "../../Header.h"

class Boss
{
protected:
    iXY Size;
    int Scale;
    int BodyColor;
    Poly MainBody;
    Poly BodyDetail1;
    Poly BodyDetail2;
public:
    Boss();
    int GetSizeX(){ return Size.x; };
    int GetSizeY(){ return Size.y; };
    void Draw(int x, int y);
};


#endif
