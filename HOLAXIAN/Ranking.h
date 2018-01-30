#ifndef RANKING_H
#define RANKING_H
#include "Color.h"
#include "Game/Text.h"

const int RANKING_TEXTS = 7;
const int RANKING_LIST_SIZE = 5;
const int SELECTED_EXIT_RANKING = 6;

class Ranking : public Text
{
private:
    int score[RANKING_LIST_SIZE];
    char players[RANKING_LIST_SIZE][6];
    bool isRankingRunning;
public:
    Ranking(bool debug_);
    ~Ranking();
    void run();
    void update();
};


#endif
