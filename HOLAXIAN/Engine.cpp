#include "Engine.h"

Engine::Engine(int width_,int height_,bool debug_)
{
    srand(time(NULL));
    height=height_;
    width=width_;
    debug=debug_;
    if(debug){
        std::cout << "DEBUG MODE\n";
    }else{
        HWND Stealth;
        AllocConsole();
        Stealth = FindWindowA("ConsoleWindowClass", NULL);
        ShowWindow(Stealth,0);
    }
    initwindow(width,height,"Holaxian",0,0,true,true);
}

void Engine::help()
{
    Help help(debug);
    help.run();
}

void Engine::ranking()
{
    Ranking ranking(debug);
    ranking.run();
}

void Engine::settings()
{
    Settings settings(debug);
    settings.run();
}

bool Engine::game(bool loadgame)
{
    Game *game = new Game(debug,loadgame);
    game->run();
    bool exit = game->exitGame;
    delete game;
    game = NULL;
    return exit;
}

//TODO Specjalny plik z funkcjami pomocnicznymi i typami np iXY fXY albo specjalna klasas np na plik input i potem dziedziczenie do gry engine itp
bool Engine::fileExist(char filename[])
{
    FILE *savedat;
    savedat=fopen(filename,"r+b");
    fclose(savedat);
    if(savedat==NULL)
    {
        if(debug){std::cout << "File not found: " << filename << "\n"; }
        return false;
    }
    else
    {
        if(debug){ std::cout << "File found: " << filename << "\n"; }
        return true;
    }
}

int Engine::run()
{
    Menu menu(debug);
    menu.render();
    while(menu.isMenuRunning)
    {
        switch(menu.state)
        {
        case MENU:
            menu.input();
            menu.update();
            break;
        case NEWGAME:
            menu.isMenuRunning=!game(false);
            menu.state=MENU;
            menu.render();
            break;
        case LOADGAME:
            if(fileExist("save.dat"))
            {
                menu.isMenuRunning=!game(true);
            }
            else
            {
                menu.showError=true;
            }
            menu.state=MENU;
            menu.render();
            break;
        case HELP:
            help();
            menu.state=MENU;
            menu.render();
            break;
        case RANKING:
            ranking();
            menu.state=MENU;
            menu.render();
            break;
        case SETTINGS:
            settings();
            menu.state=MENU;
            menu.render();
            break;
        case EXIT:
            menu.isMenuRunning=false;
            break;
        }
    }
    return 0;
}


