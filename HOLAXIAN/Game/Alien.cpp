#include "Alien.h"

Alien::Alien():MainBody(16),BodyDetail1(12),BodyDetail2(12)
{
    BodyColor = COLOR_ENEMY;
    int alien1[16]= {3,0,14,0,17,3,17,10,12,15,5,15,0,10,0,3};
    int alien2[12]= {4,4,6,4,7,5,7,8,6,8,3,5};
    int alien3[12]= {11,4,13,4,14,5,11,8,10,8,10,5};
    Scale = getmaxx()/(12.0+11.0*0.5+4.0)/18.0;
    SizeX=Scale*18.0;
    SizeY=Scale*16.0;
    MainBody.Set(alien1,BodyColor,Scale);
    BodyDetail1.Set(alien2,BLACK,Scale);
    BodyDetail2.Set(alien3,BLACK,Scale);
}

void Alien::Draw(int x, int y)
{
    MainBody.Draw(x,y);
    BodyDetail1.Draw(x,y);
    BodyDetail2.Draw(x,y);
}
