#ifndef INFOBAR_H
#define INFOBAR_H
#include "../Header.h"

class InfoBar
{
public:
    InfoBar();
    void Draw();
    void SetTime(int Time_);
    void SetScore(int Score_);
    void SetLife(int Life_);
    int GetHeight() const;
protected:
    int Color;
    int Height;
    int Width;
    char Time[25];
    char Score[25];
    char Life[25];
};

#endif
