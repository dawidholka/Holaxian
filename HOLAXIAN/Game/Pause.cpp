#include "Pause.h"

Pause::Pause(bool debug_):Text(debug_)
{
    exitGame=false;
    exitPause=false;
    gameSaved=false;
    isPauseRunning=true;
    isGameRunning=true;
    sprintf(text[0],"PAUSE");
    sprintf(text[1],"Resume Game");
    sprintf(text[2],"Save Game");
    sprintf(text[3],"Help");
    sprintf(text[4],"Exit To Menu");
    sprintf(text[5],"Exit Game");
    selected=PAUSE_BACK_TO_GAME;
    setText(PAUSE_TEXTS);
    render();
    swapbuffers();
}

void Pause::saveGame(struct gamedata &data, std::vector<PlayerMissile> &playermissile, std::vector<PlayerMissile> &bossmissile)
{
    if(debug){ printf("Zapisywanie gry\n");}
    FILE *savedat;
    savedat=fopen("save.dat","wb");
    fwrite(&data,sizeof(data),1,savedat);
    for(std::vector<PlayerMissile>::iterator it=playermissile.begin(); it < playermissile.end(); ++it)
    {
        int savex=it->x;
        int savey=it->y;
        fwrite(&savex,sizeof(savex),1,savedat);
        fwrite(&savey,sizeof(savey),1,savedat);
    }
    if(data.boss.attack&&data.boss.stage)
    {
        int savex=bossmissile[0].x;
        int savey=bossmissile[0].y;
        fwrite(&savex,sizeof(savex),1,savedat);
        fwrite(&savey,sizeof(savey),1,savedat);
    }
    fclose(savedat);
}

void Pause::help()
{
    Help help(debug);
    help.run();
}

void Pause::update(struct gamedata &data, std::vector<PlayerMissile> &playermissile, std::vector<PlayerMissile> &bossmissile)
{
    switch(code)
    {
    case KEY_UP:
        if(selected>PAUSE_BACK_TO_GAME)
        {
            selected--;
        }
        else
        {
            selected=PAUSE_EXIT_GAME;
        }
        break;
    case KEY_DOWN:
        if(selected<PAUSE_EXIT_GAME)
        {
            selected++;
        }
        else
        {
            selected=PAUSE_BACK_TO_GAME;
        }
        break;
    case KEY_ENTER:
        switch(selected)
        {
        case PAUSE_BACK_TO_GAME:
            isPauseRunning=false;
            exitPause=true;
            break;
        case PAUSE_SAVE_GAME:
            saveGame(data,playermissile,bossmissile);
            gameSaved=true;
            break;
        case PAUSE_HELP:
            help();
            break;
        case PAUSE_EXIT_TO_MENU:
            exitGame=false;
            isGameRunning=false;
            isPauseRunning=false;
            exitPause=true;
            break;
        case PAUSE_EXIT_GAME:
            isGameRunning=false;
            exitGame=true;
            isPauseRunning=false;
            exitPause=true;
            break;
        }
    case KEY_ESC:
        //isMenuRunning=NO;
        break;
    }
}

void Pause::render()
{
    Text::render(PAUSE_TEXTS);
    if(gameSaved)
    {
        setcolor(COLOR_NOTIFICATION);
        outtextxy((getmaxx()-textwidth(("GAME SAVED")))/2,getmaxy()-2*textheight("GAME SAVED"),"GAME SAVED");
    }
}

void Pause::run(bool &exitGame_, bool &isGameRunning_,struct gamedata &data, std::vector<PlayerMissile> &playermissile, std::vector<PlayerMissile> &bossmissile)
{
    while(isPauseRunning)
    {
        input();
        update(data,playermissile,bossmissile);
        render();
        swapbuffers();
    }
    exitGame_=exitGame;
    isGameRunning_=isGameRunning;
}
