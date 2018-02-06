#ifndef HELP_H
#define HELP_H
#include "Header.h"
#include "Game/Text.h"

const int HELP_SCREEN_FONT_SIZE = 4;
const int HELP_TEXTS = 8;

class Help : public Text
{
private:
    bool isHelpRunning;
public:
    Help(bool debug_);
    ~Help();
    void run();
    void update();
    void render();
};


#endif
