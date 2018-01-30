#ifndef POLY_H
#define POLY_H
#include <graphics.h>

class Poly
{
protected:
    int NumberOfPixels;
    int *Pixels;
    int Color;
    int Scale;
public:
    void Set(int T[], int color_,int scale_);
    void Draw(int x, int y);
    Poly(int N);
    ~Poly();
};

#endif
