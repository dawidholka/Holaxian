#ifndef TEXT_H
#define TEXT_H
#include <stdio.h>
#include <graphics.h>
#include "../Header.h"

const int DEFAULT_TITLE_SIZE = 10;
const int DEFAULT_FONT_SIZE = 5;
const int NO_INPUT = -1;

class Text{
protected:
    char text[8][50];
    int textPosY[8];
    int selected;
    int fontSize;
    int code;
    bool debug;
    void render(int numberOfTexts);
    void input();
    void setText(int numberOfTexts);
public:
    Text(bool debug_):debug(debug_)
    {
        fontSize=DEFAULT_FONT_SIZE;
    }
};
#endif
