#include "InfoBar.h"

InfoBar::InfoBar()
{
    Color = BLACK;
    Height=getmaxy()*0.09;
}

int InfoBar::GetHeight() const { return Height; }

void InfoBar::SetScore(int Score_)
{
    sprintf(Score,"SCORE: %d",Score_);
}

void InfoBar::SetTime(int Time_)
{
    sprintf(Time,"TIME: %d",Time_);
}

void InfoBar::SetLife(int Life_)
{
    sprintf(Life,"LIFE: %d",Life_);
}

void InfoBar::Draw()
{
    setfillstyle(SOLID_FILL,Color);
    setbkcolor(Color);
    setcolor(WHITE);
    bar(0,0,getmaxx()+1,Height);
    outtextxy(0,((Height-textheight(Score))/2),Score);
    outtextxy((getmaxx()-textwidth(Time))/2,((Height-textheight(Time))/2),Time);
    outtextxy(getmaxx()-textwidth(Life),((Height-textheight(Life))/2),Life);
}
