#ifndef POLY_H
#define POLY_H
#include <graphics.h>
#include <stdio.h>

class Poly{
protected:
    int *Pixels; // tablica pixeli
    int NumOfPixels;
    void MovePixels();
    int color;
public:
    void Draw(int x, int y);
    void wypelnij(int tab[]);
    Poly(int N, int color);
};

#endif
