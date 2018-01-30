#ifndef ENGINE_H
#define ENGINE_H
#include <stdio.h>
#include "Game.h"
#include <graphics.h>
#include <stdlib.h>
#include <time.h>
#include "Color.h"
#include "Menu.h"
#include "Help.h"
#include "Ranking.h"
#include "Settings.h"
#include <Windows.h>

class Engine
{
private:
    int width;
    int height;
    bool debug;
    void help();
    void ranking();
    void settings();
    bool game(bool load);
    bool fileExist(char filename[]);
public:
    Engine(int width_,int height_,bool debug_);
    int run();
    void input();
    void update();
    void render();
};


#endif
