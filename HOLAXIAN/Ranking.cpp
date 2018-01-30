#include "Ranking.h"

Ranking::Ranking(bool debug_):Text(debug_)
{
    if(debug)
    {
        printf("Wczytanie ekranu rankingu\n");
    }
    FILE *rankingdat;
    int status;
    rankingdat=fopen("ranking.dat","r+b");
    if(rankingdat==NULL)
    {
        fclose(rankingdat);
        rankingdat=fopen("ranking.dat","wb");
        for(int i=0; i<RANKING_LIST_SIZE; i++)
        {
            score[i]=0;
        }
        for(int i=0; i<RANKING_LIST_SIZE; i++)
        {
            sprintf(players[i],"%s","EMPTY");
        }
        status=fwrite(&score,sizeof(score),1,rankingdat);
        status=fwrite(&players,sizeof(players),1,rankingdat);
        if(status<1)
        {
            perror("Proba zapisu");
        }
        fclose(rankingdat);
    }
    else
    {
        status=fread(&score,sizeof(score),1,rankingdat);
        status=fread(&players,sizeof(players),1,rankingdat);
        if(status<1)
        {
            perror("Proba zapisu");
        }
        fclose(rankingdat);
    }
    isRankingRunning=true;
    sprintf(text[0],"RANKING");
    sprintf(text[1],"1 %s %d",players[0],score[0]);
    sprintf(text[2],"2 %s %d",players[1],score[1]);
    sprintf(text[3],"3 %s %d",players[2],score[2]);
    sprintf(text[4],"4 %s %d",players[3],score[3]);
    sprintf(text[5],"5 %s %d",players[4],score[4]);
    sprintf(text[6],"EXIT TO MENU");
    selected=SELECTED_EXIT_RANKING;
    setText(RANKING_TEXTS);
}

Ranking::~Ranking()
{
    settextstyle(GOTHIC_FONT,HORIZ_DIR,3);
}

void Ranking::run()
{
    render(RANKING_TEXTS);
    swapbuffers();
    while(isRankingRunning)
    {
        input();
        update();
    }
}

void Ranking::update()
{
    if(code==KEY_ENTER)
    {
        isRankingRunning=false;
    }
}
