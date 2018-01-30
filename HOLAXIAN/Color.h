#ifndef COLOR_H
#define COLOR_H
#include <stdio.h>
#include <iostream>
#include <graphics.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
//TODO
//ZAPISYWANIE POCISKOW BOSSA
//KOLORY
#define COLOR_STARS COLOR(166,166,166)
#define COLOR_ENEMY_MISSILE COLOR(145,255,0)
#define COLOR_HERO_MISSILE RED
#define COLOR_ENEMY COLOR(85,255,85)
#define COLOR_HERO WHITE
#define COLOR_HERO_DETAILS COLOR(191,0,0)
#define COLOR_NOTIFICATION COLOR(191,0,0)
#define COLOR_TITLE COLOR(255,255,0)
#define COLOR_BG COLOR(48,0,85)
#define COLOR_SELECTED COLOR(85,255,255)
#define COLOR_BONUS_HEALTH COLOR(191,0,0)
#define COLOR_BONUS_WEAPON COLOR(255,85,255)
#define COLOR_BOSS COLOR(255,85,85)
//KLAWISZE
#define KEY_ESC 27
#define KEY_ENTER 13
#define KEY_SPACE 32
#define KEY_BS 8
#define KEY_ENTER 13
#define KEY_ESC 27
//STANY
#define NO_MISSILE 0
#define MISSILE_LUNCHED 1
#define IN_STAGE_SCREEN 2
#define IN_GAME 1
#define NEW_GAME 2

typedef struct fXY
{
    float x;
    float y;
} fXY;

typedef struct iXY
{
    int x;
    int y;
} iXY;


class PlayerMissile{
public:
    int x;
    int y;
    PlayerMissile(int x_,int y_){
        x=x_;
        y=y_;
    }
};
#endif
