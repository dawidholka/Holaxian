#ifndef PLAYER_H
#define PLAYER_H
#pragma once
#include "../../Header.h"

class Player
{
public:
    Player();
    void SetPositionX(int X);
    void SetPositionY(int Y);
    int GetPositionX();
    int GetPositionY();
    void MoveLeft();
    void MoveRight();
protected:
    iXY Position;
};

#endif
