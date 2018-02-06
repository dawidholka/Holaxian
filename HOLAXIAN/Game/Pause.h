#ifndef PAUSE_H
#define PAUSE_H
#include "../Header.h"
#include "../Help.h"
#include "../Game.h"
#include "Text.h"

const int PAUSE_TEXTS = 6;
const int PAUSE_BACK_TO_GAME = 1;
const int PAUSE_SAVE_GAME = 2;
const int PAUSE_HELP = 3;
const int PAUSE_EXIT_TO_MENU = 4;
const int PAUSE_EXIT_GAME = 5;

class Pause : public Text
{
private:
    bool isGameRunning;
    bool exitGame;
    bool saveError;
    void update(struct gamedata &data, std::vector<PlayerMissile> &playermissile, std::vector<PlayerMissile> &bossmissile);
    void render();
    void help();
    bool gameSaved;
    void saveGame(struct gamedata &data, std::vector<PlayerMissile> &playermissile, std::vector<PlayerMissile> &bossmissile);
public:
    Pause(bool debug_);
    bool isPauseRunning;
    bool exitPause;
    void run(bool &exitGame_, bool &isGameRunning_,struct gamedata &data, std::vector<PlayerMissile> &playermissile, std::vector<PlayerMissile> &bossmissile);
};

#endif
