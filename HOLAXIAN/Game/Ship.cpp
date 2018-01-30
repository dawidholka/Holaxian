#include "Ship.h"

Ship::Ship()
{
    hero1 = new Poly(42,WHITE);
    int hero2[42]= {6,0,8,0,8,5,10,5,10,17,12,17,12,25,14,25,14,32,8,32,8,35,6,35,6,32,0,32,0,25,2,25,2,17,4,17,4,5,6,5,6,0};
    hero1->wypelnij(hero2);
}

void Ship::Draw(int x, int y)
{
    hero1->Draw(x,y);
}
