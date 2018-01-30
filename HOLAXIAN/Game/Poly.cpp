#include "Poly.h"

Poly::Poly(int N, int color):
    NumOfPixels(N),color(color)
{
    Pixels = new int[NumOfPixels];
}

void Poly::wypelnij(int tab[])
{
    for(int i=0;i<NumOfPixels;i++){
        Pixels[i] = tab[i];
    }
}

void Poly::Draw(int x, int y)
{
    for(int i=0; i<NumOfPixels; i+=2)
    {
        Pixels[i]+=x;
    }
    for(int i=1; i<NumOfPixels; i+=2)
    {
        Pixels[i]+=y;
        printf("%d\n",Pixels[i]);
    }
    printf("DRUKUJE\n");
    setcolor(WHITE);
    setfillstyle(SOLID_FILL,WHITE);
    setlinestyle(SOLID_LINE,0,NORM_WIDTH);
    fillpoly(NumOfPixels/2,(int*)NumOfPixels);
    for(int i=0; i<NumOfPixels; i+=2)
    {
        Pixels[i]-=x;
    }
    for(int i=1; i<NumOfPixels; i+=2)
    {
        Pixels[i]-=y;
    }
}
