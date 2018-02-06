#ifndef GAMEOVER_H
#define GAMEOVER_H
#include "../Header.h"
#include "../Game.h"

class GameOver
{
private:
    int place;
    bool debug;
    int scorelist[5];
    char playerslist[5][6];
    char nick[6];
    bool changeranking;
    void input();
    int code;
    bool isGameOverRunning;
public:
    GameOver(bool debugflag,int score);
    void update();
    void render();
};

#endif
