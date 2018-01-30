#ifndef BACKGROUND_H
#define BACKGROUND_H
#include <stdio.h>
#include <graphics.h>
#include "../Color.h"

const int STARS = 200;

class Background{
private:
    int stars[STARS];
public:
    Background();
    void update();
    void render();
};

#endif
