#include "Poly.h"

Poly::Poly(int N)
{
    NumberOfPixels = N;
    Pixels = new int[NumberOfPixels];
    for(int i=0;i<NumberOfPixels;++i){
        Pixels[i]=0;
    }
}

void Poly::Set(int T[],int color_,int scale_)
{
    Color = color_;
    Scale = scale_;
    for(int i=0; i<NumberOfPixels; i++)
    {
        Pixels[i]=T[i]*Scale;
    }
}

void Poly::Draw(int x, int y)
{
    setcolor(Color);
    setfillstyle(SOLID_FILL,Color);
    setlinestyle(SOLID_LINE,0,NORM_WIDTH);
    for(int i=0; i<NumberOfPixels; i+=2)
    {
        Pixels[i]+=x;
    }
    for(int i=1; i<NumberOfPixels; i+=2)
    {
        Pixels[i]+=y;
    }
    fillpoly(NumberOfPixels/2,Pixels);
        for(int i=0; i<NumberOfPixels; i+=2)
    {
        Pixels[i]+=(-x);
    }
    for(int i=1; i<NumberOfPixels; i+=2)
    {
        Pixels[i]+=(-y);
    }
}

Poly::~Poly()
{
    delete[] Pixels;
    Pixels = NULL;
    NumberOfPixels = 0;
}
