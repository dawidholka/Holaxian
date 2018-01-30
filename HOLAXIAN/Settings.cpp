#include "Settings.h"

// wczytanie ustawien z pliku settings.dat
Settings::Settings(bool debug_):Text(debug_)
{
    if(debug){ printf("Wczytanie ekranu ustawien\n"); }
    FILE *settingsdat;
    int status;
    settingsdat=fopen("settings.dat","r+b");
    if(settingsdat==NULL)
    {
        fclose(settingsdat);
        settings.agression=SETTINGS_DEFAULT_VALUE;
        settings.time=SETTINGS_DEFAULT_VALUE;
        settings.missiles=SETTINGS_DEFAULT_VALUE;
        settings.missilespeed=SETTINGS_DEFAULT_VALUE;
        settings.life=SETTINGS_DEFAULT_VALUE;
        settingsdat=fopen("settings.dat","wb");
        status=fwrite(&settings,sizeof(settings),1,settingsdat);
        if(status<1)
        {
            perror("Proba zapisu");
        }
        fclose(settingsdat);
    }
    else
    {
        status=fread(&settings,sizeof(settings),1,settingsdat);
        if(status<1)
        {
            perror("Proba zapisu");
        }
        fclose(settingsdat);
    }
}

void Settings::run()
{
    sprintf(text[0],"SETTINGS");
    sprintf(text[1],"AGRESSION x%d",settings.agression);
    sprintf(text[2],"TIME x%d",settings.time);
    sprintf(text[3],"MISSILE SPEED x%d",settings.missilespeed);
    sprintf(text[4],"LIFE %d",settings.life);
    sprintf(text[5],"MISSILES x%d",settings.missiles);
    sprintf(text[6],"SAVE");
    setText(SETTINGS_TEXTS);
    selected=SETTINGS_SAVE;
    render();
    isSettingsRunning=true;
    while(isSettingsRunning)
    {
        input();
        update();
    }
}

void Settings::update()
{
    switch(code)
    {
    case KEY_UP:
        if(selected==SETTINGS_AGRESSION)
        {
            selected=SETTINGS_SAVE;
            render();
        }
        else
        {
            --selected;
            render();
        }
        break;
    case KEY_DOWN:
        if(selected==SETTINGS_SAVE)
        {
            selected=SETTINGS_AGRESSION;
            render();
        }
        else
        {
            ++selected;
            render();
        }
        break;
    case KEY_RIGHT:
        switch(selected)
        {
        case SETTINGS_AGRESSION:
            if(settings.agression<SETTINGS_MAX_VALUE)
            {
                ++settings.agression;
                sprintf(text[SETTINGS_AGRESSION],"AGRESSION x%d",settings.agression);
                render();
            }
            break;
        case SETTINGS_TIME:
            if(settings.time<SETTINGS_MAX_VALUE)
            {
                ++settings.time;
                sprintf(text[SETTINGS_TIME],"TIME x%d",settings.time);
                render();
            }
            break;
        case SETTINGS_MISSILESPEED:
            if(settings.missilespeed<SETTINGS_MAX_VALUE)
            {
                ++settings.missilespeed;
                sprintf(text[SETTINGS_MISSILESPEED],"MISSILE SPEED x%d",settings.missilespeed);
                render();
            }
            break;
        case SETTINGS_LIFE:
            if(settings.life<SETTINGS_MAX_VALUE)
            {
                ++settings.life;
                sprintf(text[SETTINGS_LIFE],"LIFE %d",settings.life);
                render();
            }
            break;
        case SETTINGS_MISSILES:
            if(settings.missiles<SETTINGS_MAX_VALUE)
            {
                ++settings.missiles;
                sprintf(text[SETTINGS_MISSILES],"MISSILES x%d",settings.missiles);
                render();
            }
            break;
        }
        break;
    case KEY_LEFT:
        switch(selected)
        {
        case SETTINGS_AGRESSION:
            if(settings.agression>SETTINGS_MIN_VALUE)
            {
                --settings.agression;
                sprintf(text[SETTINGS_AGRESSION],"AGRESSION x%d",settings.agression);
                render();
            }
            break;
        case SETTINGS_TIME:
            if(settings.time>SETTINGS_MIN_VALUE)
            {
                --settings.time;
                sprintf(text[SETTINGS_TIME],"TIME x%d",settings.time);
                render();
            }
            break;
        case SETTINGS_MISSILESPEED:
            if(settings.missilespeed>SETTINGS_MIN_VALUE)
            {
                --settings.missilespeed;
                sprintf(text[SETTINGS_MISSILESPEED],"MISSILE SPEED x%d",settings.missilespeed);
                render();
            }
            break;
        case SETTINGS_LIFE:
            if(settings.life>SETTINGS_MIN_VALUE)
            {
                --settings.life;
                sprintf(text[SETTINGS_LIFE],"LIFE %d",settings.life);
                render();
            }
            break;
        case SETTINGS_MISSILES:
            if(settings.missiles>SETTINGS_MIN_VALUE)
            {
                --settings.missiles;
                sprintf(text[SETTINGS_MISSILES],"MISSILES x%d",settings.missiles);
                render();
            }
            break;
        }
        break;
    case KEY_ENTER:
        if(selected==SETTINGS_SAVE)
        {
            save();
            isSettingsRunning=false;
        }
        break;
    case KEY_ESC:
        isSettingsRunning=false;
        break;
    }
}

void Settings::save()
{
    FILE *settingsdat;
    int status;
    settingsdat=fopen("settings.dat","r+b");
    status=fwrite(&settings,sizeof(settings),1,settingsdat);
    if(status<1)
    {
        perror("Proba zapisu");
    }
    fclose(settingsdat);
}

void Settings::render()
{
    Text::render(SETTINGS_TEXTS);
    swapbuffers();
}

void Settings::get(SettingList *loadsettings)
{
    if(debug)
    {
        printf("Wczytywanie ustawien z pliku\n");
    }
    loadsettings->agression=settings.agression;
    loadsettings->life=settings.life;
    loadsettings->missiles=settings.missiles;
    loadsettings->missilespeed=settings.missilespeed;
    loadsettings->time=settings.time;
}
