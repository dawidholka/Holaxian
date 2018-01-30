#ifndef GAME_H
#define GAME_H
#include "Color.h"
#include "Settings.h"
#include "Help.h"
#include "Game/ParticleSystem.h"
#include "Game/Pause.h"
#include "Game/Background.h"
#include "Game/GameOver.h"
#include "Game/Ship.h"
#include "Game/Alien.h"
#include "Game/Boss.h"

struct sizeofobjects
{
    int x;
    int y;
};

struct graphics
{
    Ship PlayerShip;
    Alien Alien;
    Boss Boss;
    int player[42];
    int playerdetails[24];
    int enemy[16];
    int enemydetail1[12];
    int enemydetail2[12];
    int bossbody[16];
    int bossdetail1[12];
    int bossdetail2[12];
    int scale;
    Background background;
    ParticleSystem particles;
};

struct enemy
{
    short int lives;
    int positionX;
    int positionY;
};

struct missile
{
    short int state;
    int x;
    int y;
};

struct infobar
{
    int height;
    char time[25];
    char score[25];
    char life[25];
};

class Missile
{
public:
    int x;
    int y;
    int state;
    Missile();
};

struct bonus
{
    int x;
    int y;
    int color;
    bool drop;
};

struct boss
{
    int x;
    int y;
    bool stage;
    int life;
    int direction;
    bool attack;
};

struct gamedata
{
    int playerx;
    int playery;
    int difficulty;
    int score;
    int life;
    int stage;
    int maxplayermissile;
    int currentplayermissile;
    Missile enemymissile;
    int stagetime;
    int timeleft;
    struct enemy enemy[3][12];
    int numofenemies;
    struct bonus bonus;
    struct boss boss;
};

class Game
{
private:
    SettingList settings;
    bool debug;//TRYB DEBUG
    struct graphics graphics;
    struct sizeofobjects playersize;
    struct sizeofobjects enemysize;
    struct sizeofobjects collision;
    struct sizeofobjects bosssize;
    struct infobar infobar;
    struct gamedata data;

    void pause();
    void saveGame();
    void help();

    //POCISKI GRACZA
    std::vector<PlayerMissile> playermissile;
    void sendPlayerMissile();
    void updatePlayerMissile();
    void printPlayerMissile();
    void flushPlayerMissile(); //Czysci vector

    void updateBoss();
    std::vector<PlayerMissile> bossmissile;
    void updateBossMissile();
    void printBossMissile();
    void flushBossMissile();

    int code; //AKTUALNIE WCISNIETY KLAWISZ
    int playerspeed; //PRZESUNIECIE GRACZA W GRZE
    int missilespeed; // PREDKOSC POCISKOW W GRZE
    int enemymissilespeed; // PREDKOSC POCISKOW PRZECIWNIKA
    int chancetoattack; //PRAWDOPODOBIENSTWO ZATAKOWANIA GRACZA
    //GRAFICZNE FUNCKJE
    void scalePoly(int poly, int pixele[],int skala);
    void printPoly(int x,int y,int kolor,int siatka[],int rozmiarsiatki,int polsiatki);
    void movePoly(int x, int y, int siatka[],int rozmiarsiatki);
    void printEnemies();
    void printInfoBar();
    void printMissile(int x,int y,int color);
    //USTAWIANIE PRZECIWNIKOW
    void assortingEnemies(int difficulty,struct enemy enemy[][12]);
    void setEnemies();
    bool isAlreadyDrawn(int num,int tab[],int how);//SPRAWDZA CZY LICZBA ZNAJDUJE SIE JUZ W TABELI
    int timeendstage;
    int frame;
    void attackingPlayer();
    void moveEnemyMissile();
    void updateTime();
    int freezetime;
    int stagescreenon;
    char stagetext[25];
    void newStage();
    int gamestatus;

    void gameOver();
    //BONUS DLA GRACZA
    void printBonus();
    void updateBonus();
    void input();//Przechwytywanie klawiatury
    void update();//Aktualizacja swiata gry
    void render();//Drukowanie swiata gry
    bool isGameRunning;
public:
    Game(bool debugflag,bool loadgame);
    void run();
    bool exitGame;
};

#endif
