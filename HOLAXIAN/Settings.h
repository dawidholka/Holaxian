#ifndef SETTINGS_H
#define SETTINGS_H
#include "Color.h"
#include "Game/Text.h"

const int SETTINGS_TEXTS = 7;
const int SETTINGS_AGRESSION = 1;
const int SETTINGS_TIME = 2;
const int SETTINGS_MISSILESPEED = 3;
const int SETTINGS_LIFE = 4;
const int SETTINGS_MISSILES = 5;
const int SETTINGS_SAVE = 6;
const int SETTINGS_MAX_VALUE = 10;
const int SETTINGS_MIN_VALUE = 1;
const int SETTINGS_DEFAULT_VALUE = 1;

typedef struct settings
{
    int agression;
    int time;
    int missilespeed;
    int life;
    int missiles;
} SettingList;

class Settings : public Text
{
private:
    SettingList settings;
    bool isSettingsRunning;
    void help();
    void ranking();
    void save();
public:
    Settings(bool debug_); //Czyta ustawienia z pliku
    void run();
    void get(SettingList *loadsettings);
    void update();
    void render();
};


#endif
