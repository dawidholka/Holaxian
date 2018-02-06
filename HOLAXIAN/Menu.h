#ifndef MENU_H
#define MENU_H
#include "Header.h"
#include "Game/Text.h"

const int MENU_TEXTS = 7;
const int MENU_FIRST_SELECTED = 1;
const int MENU_LAST_SELECTED = 6;

enum states {MENU, NEWGAME, LOADGAME, HELP, RANKING, SETTINGS, EXIT};

class Menu : public Text
{
public:
    Menu(bool debugflag);
    bool showError;
    states state;
    bool isMenuRunning;
    void input();
    void update();
    void render();
};

#endif
