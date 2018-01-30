#include "Game.h"

Game::Game(bool debugflag,bool loadgame)
{
    //WCZYTYWANIE USTAWIEN Z PLIKU
    debug=debugflag;
    Settings *getsettings = new Settings(debug);
    getsettings->get(&settings);
    delete getsettings;
    getsettings=NULL;


    //GRAFIKA
    //graphics.playership = new Ship;
    Graphics.scale=getmaxy()*0.05/14.0;
    PlayerSize.x=Graphics.scale*14;
    PlayerSize.y=Graphics.scale*36;
    Graphics.scale = getmaxx()/(12.0+11.0*0.5+4.0)/18.0;
    EnemySize.x = Graphics.scale*18.0;
    EnemySize.y = Graphics.scale*16.0;
    BossSize.x=EnemySize.x*3;
    BossSize.y=EnemySize.y*3;
    enemymissilespeed=2;
    chancetoattack=150;
    frame=0;
    playerspeed=10;
    data.bonus.drop=false;
    missilespeed=2*settings.missilespeed;
    enemymissilespeed=2*settings.missilespeed;
    if(loadgame)
    {
        if(debug){ std::cout << "LOADING GAME FROM SAVE\n"; }
        FILE *savedat;
        savedat=fopen("save.dat","r+b");
        fread(&data,sizeof(data),1,savedat);
        timeendstage=data.timeleft+time(NULL);
        for(int missilestoload=data.currentplayermissile; missilestoload>0; --missilestoload)
        {
            int x;
            int y;
            fread(&x,sizeof(x),1,savedat);
            fread(&y,sizeof(y),1,savedat);
            playermissile.push_back(PlayerMissile(x,y));
        }
        if(data.boss.attack)
        {
            int x;
            int y;
            fread(&x,sizeof(x),1,savedat);
            fread(&y,sizeof(y),1,savedat);
            int dx=BossSize.x/4;
            for(int i=0; i<5; i++)
            {
                bossmissile.push_back(PlayerMissile((x+i*dx),(y)));
            }
        }
        fclose(savedat);
    }
    else
    {
        //NOWA GRA
        if(debug){ std::cout << "NEW GAME\n"; }
        data.boss.stage=false;
        data.enemymissile.state=NO_MISSILE;
        data.score=0;
        data.maxplayermissile=settings.missiles;
        data.currentplayermissile=0;
        data.difficulty=settings.agression;
        data.life=settings.life;
        data.stage=1;
        data.bonus.drop=false;
        assortingEnemies(data.difficulty,data.enemy);
        setEnemies();
        data.stagetime=data.numofenemies*4*settings.time;
        data.timeleft=data.stagetime;
        data.playerx=(getmaxx()-PlayerSize.x)/2;
        data.playery=getmaxy()-(PlayerSize.y*1.5);
    }
    exitGame=false;
    gamestatus=IN_STAGE_SCREEN;
    //sprintf(infobar.score,"SCORE: %d",data.score);
    //sprintf(infobar.time,"TIME: %d",data.timeleft);
    //sprintf(infobar.life,"LIFE: %d",data.life);
    sprintf(stagetext,"STAGE: %d",data.stage);

    Bar = new InfoBar;
    Bar->SetScore(data.score);
    Bar->SetLife(data.life);
    Bar->SetTime(data.timeleft);
    isGameRunning=true;
    settextstyle(GOTHIC_FONT,HORIZ_DIR,3);
}

void Game::run()
{
    while(isGameRunning)
    {
        input();
        update();
        render();
        delay(15);
        swapbuffers();
    }
}

Missile::Missile()
{
    state=NO_MISSILE;
}

void Game::sendPlayerMissile()
{
    if(data.currentplayermissile<data.maxplayermissile)
    {
        playermissile.push_back(PlayerMissile((data.playerx+(PlayerSize.x/2)),(data.playery-25)));
        ++data.currentplayermissile;
        if(debug)
        {
            printf("Wysylam pocisk\n");
        }
    }
}

void Game::updateBossMissile()
{
    for(std::vector<PlayerMissile>::iterator it=bossmissile.begin(); it < bossmissile.end(); ++it)
    {
        if(getpixel(it->x,it->y+25)==COLOR_HERO)
        {
            if(debug)
            {
                printf("Boss trafil gracza\n");
            }
            bossmissile.erase(it--);
            --data.life;
            Bar->SetLife(data.life);
            data.playerx=(800-PlayerSize.x)/2;
            data.boss.attack=false;
        }
        else
        {
            if(it->y>getmaxy())
            {
                bossmissile.erase(it--);
                data.boss.attack=false;
            }
            else
            {
                it->y+=enemymissilespeed;
            }
        }
    }
    if(bossmissile.empty())
    {
        data.boss.attack=false;
    }
    if(data.boss.attack==false&&!bossmissile.empty())
    {
        flushBossMissile();
    }
}

void Game::printBossMissile()
{
    for(std::vector<PlayerMissile>::iterator it=bossmissile.begin(); it < bossmissile.end(); ++it)
    {
        printMissile(it->x,it->y,COLOR_ENEMY_MISSILE);
    }
}

void Game::updatePlayerMissile()
{
    for(std::vector<PlayerMissile>::iterator it=playermissile.begin(); it < playermissile.end(); ++it)
    {
        if(data.boss.stage)
        {
            if(getpixel(it->x,it->y-1)==COLOR_BOSS)
            {
                if(debug)
                {
                    printf("Gracz trafil bossa\n");
                }
                playermissile.erase(it--);
                --data.currentplayermissile;
                ++data.score;
                --data.boss.life;
                Bar->SetScore(data.score);
            }
            else
            {
                if(it->y<Bar->GetHeight())
                {
                    playermissile.erase(it--);
                    --data.currentplayermissile;
                }
                else
                {
                    it->y-=missilespeed;
                }
            }
        }
        else
        {
            if(getpixel(it->x,it->y-1)==COLOR_ENEMY)
            {
                for(int k=0; k<12; k++)
                {
                    if(it->x>=data.enemy[0][k].positionX&&it->x<=(data.enemy[0][k].positionX+EnemySize.x*1))
                    {
                        Collision.x=k;
                    }
                }
                for(int w=0; w<3; w++)
                {
                    if(it->y>=data.enemy[w][Collision.x].positionY)
                    {
                        Collision.y=w;
                    }
                }
                data.enemy[Collision.y][Collision.x].lives--;
                ++data.score;
                Bar->SetScore(data.score);
                playermissile.erase(it--);
                --data.currentplayermissile;
                data.numofenemies--;
                rand();
                if(debug)
                {
                    printf("Gracz trafil przeciwnika %d %d\n",Collision.y,Collision.x);
                }
                if(data.bonus.drop==false&&data.numofenemies>0)
                {
                    if(debug)
                    {
                        printf("Losuje bonus dla gracza\n");
                    }
                    if((rand()/(float(RAND_MAX)+1)*100)<=(50))  //50% szansy na bonus
                    {
                        if(debug)
                        {
                            printf("Gracz otrzymuje bonus\n");
                        }
                        data.bonus.drop=true;
                        if(debug)
                        {
                            printf("Losuje typ bonusu dla gracza\n");
                        }
                        if((rand()/(float(RAND_MAX)+1)*100)<=(50))
                        {
                            data.bonus.color=COLOR_BONUS_HEALTH; // ZYCKO
                        }
                        else
                        {
                            data.bonus.color=COLOR_BONUS_WEAPON; // DODATKOWY POCISK
                        }
                        data.bonus.x=data.enemy[Collision.y][Collision.x].positionX+EnemySize.x/2-10;
                        data.bonus.y=data.enemy[Collision.y][Collision.x].positionY;
                    }
                }
            }
            else
            {
                it->y-=missilespeed;
            }
            if(it->y<Bar->GetHeight())
            {
                playermissile.erase(it--);
                --data.currentplayermissile;
            }
        }
    }
}

void Game::printPlayerMissile()
{
    for(std::vector<PlayerMissile>::iterator it=playermissile.begin(); it < playermissile.end(); ++it)
    {
        printMissile(it->x,it->y,RED);
    }
}

void Game::printMissile(int x,int y,int color)
{
    setfillstyle(SOLID_FILL,color);
    bar(x,y,x+3,y+25);
}

void Game::assortingEnemies(int difficulty,struct enemy enemy[][12])
{
    //LOSOWE ROZMIESZCZENIE PRZECIWNKÓW NA PODSTAWIE POZIOMU TRUDNOSCI
    int c=0;
    do
    {
        if(debug)
        {
            printf("Dobieranie przeciwnikow\n");
        }
        for(int i=0; i<3; i++)
        {
            for(int j=0; j<12; j++)
            {
                if((rand()/(float(RAND_MAX)+1)*100)<=(difficulty*10))
                {
                    enemy[i][j].lives=1;
                    ++c;
                }
                else
                {
                    enemy[i][j].lives=0;
                }
                if(debug)
                {
                    printf("%d ",enemy[i][j].lives);
                }
            }
            if(debug)
            {
                printf("\n");
            }
        }
    }
    while(c==0);
}

void Game::setEnemies()
{
    data.numofenemies=0;
    for(int w=0,py=getmaxy()*0.15; w<3; w++,py+=(EnemySize.y*1.5))
    {
        for(int k=0,px=(EnemySize.x*2); k<12; k++,px+=(EnemySize.x*1.5))
        {
            data.enemy[w][k].positionX=px;
            data.enemy[w][k].positionY=py;
            if(data.enemy[w][k].lives==1)
            {
                data.numofenemies++;
            }
        }
    }
    if(debug)
    {
        printf("Liczba przeciwnikow %d\n",data.numofenemies);
    }
}

void Game::printEnemies()
{
    if(data.boss.stage)
    {
        Graphics.Boss.Draw(data.boss.x,data.boss.y);
    }
    else
    {
        for(int w=0; w<3; w++)
        {
            for(int k=0; k<12; k++)
            {
                if(data.enemy[w][k].lives==1)
                {
                    Graphics.Alien.Draw(data.enemy[w][k].positionX,data.enemy[w][k].positionY);
                }
            }
        }
    }
}

void Game::updateTime()
{
    if((timeendstage-time(NULL))!=data.timeleft)
    {
        data.timeleft = timeendstage-time(NULL);
        Bar->SetTime(data.timeleft);
        data.stagetime=data.timeleft;
    }
}

void Game::saveGame()
{
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
    fclose(savedat);
}

void Game::input()
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
        //Jesli gracz nic nie wcisnal to zmien kod
        code=-1;
    }
}

bool Game::isAlreadyDrawn(int num,int tab[],int how)
{
    //Losowanie bez powtorzen
    if(how<=0)
    {
        return false;
    }
    int i=0;
    do
    {
        if(tab[i]==num)
        {
            return true;
        }
        ++i;
    }
    while(i<how);
    return false;
}

void Game::attackingPlayer()
{
    if(!data.boss.stage)
    {
        if(((data.enemymissile.state)==NO_MISSILE)&&((frame%chancetoattack)==0))
        {
            if(debug)
            {
                printf("Losowanie przeciwnika\n");
            }
            int alreadydrawn[12];
            int numofalreadydrawn=0;
            int numofdraw=0;
            int line,column;
            line=-1;
            column=-1;
            rand();//Bo pierwsza wylosowana liczba sie czestopotwarza
            do
            {
                do
                {
                    column=rand()/(float(RAND_MAX)+1)*12;
                    if(isAlreadyDrawn(column,alreadydrawn,numofalreadydrawn)==false)
                    {
                        if(debug)
                        {
                            printf("Wylosowana kolumna: %d\n",column);
                        }
                        alreadydrawn[numofalreadydrawn]=column;
                        numofalreadydrawn++;
                    }
                }
                while(numofalreadydrawn<numofdraw);
                for(int j=2; j>=0&&line==-1; j--)
                {
                    if(data.enemy[j][column].lives==1)
                    {
                        line=j;
                    }
                }
                numofdraw++;
            }
            while(line==-1&&numofdraw<=12);
            if(debug)
            {
                printf("Atakuje przeciwnik %d %d\n",line,column);
            }
            data.enemymissile.x=(data.enemy[line][column].positionX+EnemySize.x/2);
            data.enemymissile.y=data.enemy[line][column].positionY+EnemySize.y;
            data.enemymissile.state=MISSILE_LUNCHED;
        }
    }
}

void Game::moveEnemyMissile()
{
    if(data.enemymissile.state==MISSILE_LUNCHED)
    {
        if(getpixel(data.enemymissile.x,data.enemymissile.y+25)==WHITE)
        {
            if(debug)
            {
                printf("Przeciwnik trafil gracza! \n");
            }
            --data.life;
            Bar->SetLife(data.life);
            data.playerx=(getmaxx()-PlayerSize.x)/2;
            data.enemymissile.state=NO_MISSILE;
        }
        if(data.enemymissile.y<getmaxy())
        {
            data.enemymissile.y+=enemymissilespeed;
        }
        else
        {
            data.enemymissile.state=NO_MISSILE;
        }
    }
}

void Game::newStage()
{
    if(debug)
    {
        printf("Brak przeciwnikow - Nowy poziom\n");
    }
    ++data.stage;
    ++data.difficulty;
    if(data.stage%5==0)
    {
        data.boss.stage=true;
        data.boss.direction=rand()/(float(RAND_MAX)+1)*2;
        data.boss.life=data.stage*5;
        data.boss.x=(getmaxx()-BossSize.x)/2;
        data.boss.y=getmaxy()*0.15;
        data.stagetime=data.stage*50;
        if(debug)
        {
            printf("Boss stage\n");
        }
    }
    else
    {
        data.boss.stage=false;
        assortingEnemies(data.difficulty,data.enemy);
        setEnemies();
        data.stagetime=data.numofenemies*4*settings.time;
        if(debug)
        {
            printf("Normal stage\n");
        }
    }
    data.enemymissile.state=NO_MISSILE;
    data.bonus.drop=false;
    gamestatus=IN_STAGE_SCREEN;
    sprintf(stagetext,"STAGE: %d",data.stage);
    data.playerx=(getmaxx()-PlayerSize.x)/2;
    data.playery=getmaxy()-(PlayerSize.y*1.5);
    flushPlayerMissile();
    flushBossMissile();
}

void Game::flushPlayerMissile()
{
    for(std::vector<PlayerMissile>::iterator it=playermissile.begin(); it < playermissile.end(); ++it)
    {
        --data.currentplayermissile;
        playermissile.erase(it--);
    }
}

void Game::flushBossMissile()
{
    for(std::vector<PlayerMissile>::iterator it=bossmissile.begin(); it < bossmissile.end(); ++it)
    {
        bossmissile.erase(it--);
    }
}

void Game::pause()
{
    Pause pause(debug);
    pause.run(exitGame,isGameRunning,data,playermissile,bossmissile);
    timeendstage=data.timeleft+time(NULL);
}

void Game::help()
{
    Help help(debug);
    help.run();
    timeendstage=data.timeleft+time(NULL);
}

void Game::updateBonus()
{
    if(data.bonus.drop)
    {
        if((getpixel(data.bonus.x,data.bonus.y+10)==WHITE)||(getpixel(data.bonus.x+20,data.bonus.y+10)==WHITE))
        {
            if(debug)
            {
                printf("Gracz zlapal bonus!\n");
            }
            if(data.bonus.color==COLOR_BONUS_HEALTH)
            {
                Bar->SetLife(++data.life);
            }
            else
            {
                ++data.maxplayermissile;
            }
            data.bonus.drop=false;
        }
        if(data.bonus.y<getmaxy())
        {
            data.bonus.y+=enemymissilespeed;
        }
        else
        {
            data.bonus.drop=false;
        }
    }
}

void Game::printBonus()
{
    if(data.bonus.drop)
    {
        setfillstyle(SOLID_FILL,data.bonus.color);
        bar(data.bonus.x,data.bonus.y,data.bonus.x+20,data.bonus.y+10);
    }
}

void Game::gameOver()
{
    GameOver gameover(debug,data.score);
    isGameRunning=false;
}

void Game::updateBoss()
{
    if(data.boss.direction==0)
    {
        if(data.boss.x>0)
        {
            --data.boss.x;
        }
        else
        {
            //data.boss.y+=10;
            data.boss.direction=1;
        }
    }
    else
    {
        if((data.boss.x+BossSize.x)<getmaxx())
        {
            ++data.boss.x;
        }
        else
        {
            //data.boss.y+=10;
            data.boss.direction=0;
        }
    }
    if((data.boss.attack==false)&&((frame%chancetoattack)==0))
    {
        if(debug)
        {
            printf("Boss atakuje!\n");
        }
        data.boss.attack=true;
        int dx=BossSize.x/4;
        for(int i=0; i<5; i++)
        {
            bossmissile.push_back(PlayerMissile((data.boss.x+i*dx),(data.boss.y+BossSize.y)));
        }
    }
    if(data.boss.attack==true)
    {
        updateBossMissile();
    }
}

void Game::update()
{
    switch(gamestatus)
    {
    case IN_GAME:
        if(data.life<1)
        {
            gameOver();
        }
        if(data.timeleft<0)
        {
            gameOver();
        }
        if(data.boss.stage)
        {
            updateBoss();
            if(data.boss.life==0)
            {
                newStage();
            }
        }
        else
        {
            if(data.numofenemies==0)
            {
                newStage();
            }
        }
        updateTime();
        updatePlayerMissile();
        updateBonus();
        attackingPlayer();
        Graphics.Background.update();
        moveEnemyMissile();
        switch(code)
        {
        case KEY_RIGHT:
            if(data.playerx<(getmaxx()-PlayerSize.x*2))
            {
                data.playerx+=playerspeed;
            }
            break;
        case KEY_LEFT:
            if(data.playerx>PlayerSize.x)
            {
                data.playerx-=playerspeed;
            }
            break;
        case KEY_UP:
            sendPlayerMissile();
            break;
        case KEY_ESC:
            pause();
            //gamestatus=IN_PAUSE_SCREEN;
            freezetime=data.timeleft;
            settextstyle(GOTHIC_FONT,HORIZ_DIR,3);
            break;
        case KEY_F1:
            help();
            break;
        }
        frame++;
        break;
    case IN_STAGE_SCREEN:
        if(code!=-1)
        {
            stagescreenon=false;
            gamestatus=IN_GAME;
            timeendstage=data.stagetime+time(NULL);
            data.timeleft=timeendstage-time(NULL);
        }
        break;
    }
}

void Game::render()
{
    switch(gamestatus)
    {
    case IN_GAME:
        setbkcolor(COLOR_BG);
        cleardevice();
        Graphics.PlayerShip.Draw(data.playerx,data.playery);
        Graphics.Background.render();
        printEnemies();
        //printInfoBar();
        Bar->Draw();
        printBonus();
        Graphics.Particles.run(data.playerx+PlayerSize.x/2-1,data.playery+PlayerSize.y-2);
        printPlayerMissile();
        if(data.boss.stage)
        {
            printBossMissile();
        }
        if(data.enemymissile.state==MISSILE_LUNCHED)
        {
            printMissile(data.enemymissile.x,data.enemymissile.y,COLOR_ENEMY_MISSILE);
        }
        break;
    case IN_STAGE_SCREEN:
        setbkcolor(COLOR_BG);
        cleardevice();
        settextstyle(GOTHIC_FONT,HORIZ_DIR,5);
        setcolor(COLOR_TITLE);
        outtextxy((getmaxx()-textwidth(stagetext))/2,((getmaxy()-textheight(stagetext))/2),stagetext);
        settextstyle(GOTHIC_FONT,HORIZ_DIR,3);
        setcolor(WHITE);
        outtextxy((getmaxx()-textwidth("PRESS ANY KEY TO PLAY"))/2,((2*textheight("PRESS ANY KEY TO PLAY"))/2),"PRESS ANY KEY TO PLAY");
        break;
    }
}

Game::~Game()
{
    delete Bar;
    Bar = NULL;
}
