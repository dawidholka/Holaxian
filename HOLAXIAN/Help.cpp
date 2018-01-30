#include "Help.h"

Help::Help(bool debug_):Text(debug_)
{
    if(debug)
    {
        printf("Wczytanie ekranu pomocy\n");
    }
    fontSize = HELP_SCREEN_FONT_SIZE;
    isHelpRunning=true;
    code=NO_INPUT;
    selected=-1;
    sprintf(text[0],"HELP");
    sprintf(text[1],"Press left or right arrow to move");
    sprintf(text[2],"You must destroy enemy spaces ship in time");
    sprintf(text[3],"Press space bar to fire your gun at them");
    sprintf(text[4],"Be careful, because these ships fire back!");
    sprintf(text[5],"Press F1 to show HELP in game");
    sprintf(text[6],"Press ESC in game to pause/save");
    sprintf(text[7],"Press ESC now to exit help screen");
    setText(HELP_TEXTS);
}

// powrot do normalnej czcionki na pasku informacji w grze
Help::~Help()
{
    settextstyle(GOTHIC_FONT,HORIZ_DIR,3);
}

void Help::run()
{
    render();
    while(code!=KEY_ESC)
    {
        input();
    }
}

void Help::render()
{
    Text::render(HELP_TEXTS);
    swapbuffers();
}
