#include "Text.h"

void Text::render(int numberOfTexts)
{
    setbkcolor(COLOR_BG);
    cleardevice();
    setcolor(COLOR_TITLE);
    settextstyle(BOLD_FONT,0,DEFAULT_TITLE_SIZE);
    outtextxy((getmaxx()-textwidth(text[0]))/2, textPosY[0], text[0]);
    settextstyle(SANS_SERIF_FONT,0,fontSize);
    setcolor(WHITE);
    for(int i=1; i<numberOfTexts; i++)
    {
        outtextxy((getmaxx()-textwidth(text[i]))/2,textPosY[i],text[i]);
    }
    if(selected>0)
    {
        setcolor(COLOR_SELECTED);
        outtextxy((getmaxx()-textwidth(text[selected]))/2,textPosY[selected],text[selected]);
    }
}

void Text::input()
{
    if(kbhit())
    {
        code=getch();
        switch(code)
        {
        case 0:
        case 224:
            code = getch();
        }
    }
    else
    {
        code=NO_INPUT;
    }
}

void Text::setText(int numberOfTexts)
{
    textPosY[0] = 5;
    settextstyle(BOLD_FONT,0,10);
    int titleheight = textheight(text[0]);
    settextstyle(SANS_SERIF_FONT,0,fontSize);
    for(int i=1; i<numberOfTexts; i++)
    {
        textPosY[i]=(15+titleheight)+(i-1)*(textheight(text[i])+5);
    }
}
