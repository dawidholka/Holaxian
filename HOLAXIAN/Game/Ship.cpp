#include "Ship.h"

Ship::Ship():MainBody(42),BodyDetail(24)
{
    int hero1[42]= {6,0,8,0,8,5,10,5,10,17,12,17,12,25,14,25,14,32,8,32,8,35,6,35,6,32,0,32,0,25,2,25,2,17,4,17,4,5,6,5,6,0};
    int hero2[24]= {6,19,8,19,8,21,10,21,10,24,8,24,8,22,6,22,6,24,4,24,4,21,6,21};
    Scale = getmaxy()*0.05/14.0;
    SizeX=Scale*14;
    SizeY=Scale*36;
    MainBody.Set(hero1,WHITE,Scale);
    BodyDetail.Set(hero2,RED,Scale);
}

void Ship::Draw(int x, int y)
{
    MainBody.Draw(x,y);
    BodyDetail.Draw(x,y);
}
