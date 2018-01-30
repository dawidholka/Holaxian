#include "GameOver.h"

void GameOver::input()
{
    if(kbhit())
    {
        code=getch();
        switch(code)
        {
        case 0:
        case 224:
            code = getch();
        }
    }
    else
    {
        code=-1;
    }
}

GameOver::GameOver(bool debugflag,int score)
{
    debug=debugflag;
    isGameOverRunning=true;
    if(debug)
    {
        printf("Koniec Gry!\n");
    }
    for(int i=0; i<6; ++i)
    {
        nick[i]='\0';
    }
    int status;
    changeranking=false;
    FILE *rankingdat;
    rankingdat=fopen("ranking.dat","r+b");
    if(rankingdat==NULL)
    {
        if(debug)
        {
            printf("Brak pliku ranking.dat\n");
        }
        fclose(rankingdat);
        rankingdat=fopen("ranking.dat","wb");
        for(int i=0; i<5; i++)
        {
            scorelist[i]=0;
        }
        for(int i=0; i<5; i++)
        {
            sprintf(playerslist[i],"%s","EMPTY");
        }
        status=fwrite(&scorelist,sizeof(scorelist),1,rankingdat);
        status=fwrite(&playerslist,sizeof(playerslist),1,rankingdat);
        if(status<1)
        {
            perror("Proba zapisu");
        }
        fclose(rankingdat);
    }
    else
    {
        if(debug)
        {
            printf("Wczytuje plik ranking.dat\n");
        }
        status=fread(&scorelist,sizeof(scorelist),1,rankingdat);
        status=fread(&playerslist,sizeof(playerslist),1,rankingdat);
        if(status<1)
        {
            perror("Proba zapisu");
        }
        fclose(rankingdat);
    }
    if(debug)
    {
        printf("Szukam miejsca dla gracza w rankingu\n");
    }
    for(int j=0; j<5&&changeranking!=true; j++)
    {
        if(score>scorelist[j])
        {
            changeranking=true;
            place=j;
            if(debug)
            {
                printf("Wolne miejsce pod indeksem %d\n",j);
            }
        }
    }
    setactivepage(3);
    setvisualpage(3);
    setbkcolor(COLOR_BG);
    settextstyle(GOTHIC_FONT,HORIZ_DIR,5);
    setcolor(COLOR_SELECTED);
    cleardevice();
    outtextxy((getmaxx()-textwidth("GAME OVER"))/2,((2*textheight("GAME OVER"))/2),"GAME OVER");
    setcolor(WHITE);
    settextstyle(GOTHIC_FONT,HORIZ_DIR,3);
    outtextxy((getmaxx()-textwidth("PRESS ESC TO RETURN TO MENU"))/2,(getmaxy()-(2*textheight("PRESS ESC TO RETURN TO MENU"))),"PRESS ESC TO RETURN TO MENU");
    char text[100];
    sprintf(text,"YOUR SCORE: %d",score);
    outtextxy((getmaxx()-textwidth(text))/2,(getmaxy()/2)-textheight(text)*2,text);
    if(changeranking)
    {
        sprintf(text,"NEW PLACE IN RANKING: %d",place+1);
        outtextxy((getmaxx()-textwidth(text))/2,(getmaxy()/2),text);
        outtextxy((getmaxx()-textwidth("PRESS ENTER TO SAVE SCORE"))/2,(getmaxy()/2)+textheight("PRESS ENTER TO SAVE SCORE")*2,"PRESS ENTER TO SAVE SCORE");
    }
    int index=0; //znak_max to 4 jak zapisze sie 4 to koniec
    do
    {
        input();
        switch(code)
        {
        case KEY_ENTER:
            if(changeranking)
            {
                //PRZESUWA TABLICE W PRAWO I ROBI MIEJSCE NA WYNIK GRACZA POD INDEKSEM PLACE
                for(int j=4; j>place; j--)
                {
                    scorelist[j]=scorelist[j-1];
                }
                scorelist[place]=score;
                cleardevice();
                settextstyle(GOTHIC_FONT,HORIZ_DIR,5);
                setcolor(COLOR_SELECTED);
                outtextxy((getmaxx()-textwidth("ENTER YOUR NICK"))/2,((2*textheight("ENTER YOUR NICK"))/2),"ENTER YOUR NICK");
                setcolor(WHITE);
                settextstyle(GOTHIC_FONT,HORIZ_DIR,3);
                outtextxy((getmaxx()-textwidth("PRESS ENTER TO SAVE"))/2,(getmaxy()-(2*textheight("PRESS ENTER TO SAVE"))),"PRESS ENTER TO SAVE");
                do
                {
                    while(kbhit())
                    {
                        code=getch();
                        if(index<5)
                        {
                            if((code>='A')&&code<='Z')
                            {
                                setcolor(COLOR_BG);
                                outtextxy((getmaxx()-textwidth(nick))/2,(getmaxy()-(textheight(nick)))/2,nick);
                                setcolor(WHITE);
                                nick[index]=code;
                                outtextxy((getmaxx()-textwidth(nick))/2,(getmaxy()-(textheight(nick)))/2,nick);
                                index++;
                            }
                            if((code>='a')&&code<='z')
                            {
                                code-=32;
                                setcolor(COLOR_BG);
                                outtextxy((getmaxx()-textwidth(nick))/2,(getmaxy()-(textheight(nick)))/2,nick);
                                setcolor(WHITE);
                                nick[index]=code;
                                outtextxy((getmaxx()-textwidth(nick))/2,(getmaxy()-(textheight(nick)))/2,nick);
                                index++;
                            }
                        }
                        if(index==0&&code==KEY_ENTER)
                        {
                            setcolor(COLOR_HERO_DETAILS);
                            outtextxy((getmaxx()-textwidth("PODAJ PRZYNAJMNIEJ JEDEN ZNAK"))/2,(getmaxy()-(4*textheight("PODAJ PRZYNAJMNIEJ JEDEN ZNAK"))),"PODAJ PRZYNAJMNIEJ JEDEN ZNAK");
                            setcolor(WHITE);
                        }
                        if(index>0&&code==KEY_BS)
                        {
                            setcolor(COLOR_BG);
                            outtextxy((getmaxx()-textwidth(nick))/2,(getmaxy()-(textheight(nick)))/2,nick);
                            setcolor(WHITE);
                            index--;
                            nick[index]='\0';
                            outtextxy((getmaxx()-textwidth(nick))/2,(getmaxy()-(textheight(nick)))/2,nick);
                        }
                        if(index>0&&code==KEY_ENTER)
                        {
                            changeranking=false;
                            isGameOverRunning=false;
                            for(int p=4; p>place; p--)
                            {
                                sprintf(playerslist[p],"%s",playerslist[p-1]);
                            }
                            sprintf(playerslist[place],"%s",nick);
                            rankingdat=fopen("ranking.dat","w+b");
                            status=fwrite(&scorelist,sizeof(scorelist),1,rankingdat);
                            status=fwrite(&playerslist,sizeof(playerslist),1,rankingdat);
                            if(status<1)
                            {
                                perror("Proba zapisu");
                            }
                            fclose(rankingdat);
                        }
                    }
                }
                while(changeranking!=false);
            }
            break;
        }
    }
    while(code!=KEY_ESC&&isGameOverRunning!=false);
}
