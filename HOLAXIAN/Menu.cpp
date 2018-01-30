#include "Menu.h"

Menu::Menu(bool debug_):Text(debug_)
{
    state=MENU;
    showError=false;
    isMenuRunning=true;
    sprintf(text[0],"HOLAXIAN");
    sprintf(text[1],"New Game");
    sprintf(text[2],"Load Game");
    sprintf(text[3],"Help");
    sprintf(text[4],"Ranking");
    sprintf(text[5],"Settings");
    sprintf(text[6],"Exit");
    selected=MENU_FIRST_SELECTED;
    setText(MENU_TEXTS);
    render();
}

void Menu::input()
{
    Text::input();
}

void Menu::update()
{
    switch(code)
    {
    case KEY_UP:
        if(selected>MENU_FIRST_SELECTED)
        {
            selected--;
        }
        else
        {
            selected=MENU_LAST_SELECTED;
        }
        render();
        break;
    case KEY_DOWN:
        if(selected<MENU_LAST_SELECTED)
        {
            selected++;
        }
        else
        {
            selected=MENU_FIRST_SELECTED;
        }
        render();
        break;
    case KEY_ENTER:
        switch(selected)
        {
        case NEWGAME:
            state=NEWGAME;
            break;
        case LOADGAME:
            state=LOADGAME;
            break;
        case HELP:
            state=HELP;
            break;
        case RANKING:
            state=RANKING;
            break;
        case SETTINGS:
            state=SETTINGS;
            break;
        case EXIT:
            state=EXIT;
            break;
        }
        break;
    case KEY_ESC:
        isMenuRunning=false;
        break;
    }
}

void Menu::render()
{
    Text::render(MENU_TEXTS);
    if(showError)
    {
        setcolor(COLOR_NOTIFICATION);
        outtextxy((getmaxx()-textwidth(("SAVE NOT FOUND")))/2,getmaxy()-2*textheight("SAVE NOT FOUND"),"SAVE NOT FOUND");
        showError=false;
    }
    swapbuffers();
}
