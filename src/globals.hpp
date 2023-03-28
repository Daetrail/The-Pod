#pragma once

#include <Arduino.h>

enum STATES : unsigned int
{
    MainMenu = 1,
    FlashMenu,
    SDCardMenu,
    Off
};

enum MM_SELECT : unsigned int
{
    Flash = 0,
    SDCard
};

struct Global
{
    static const unsigned int PIN_DISPLAY_SCL;
    static const unsigned int PIN_DISPLAY_SDA;
    static const unsigned int SCREEN_WIDTH;
    static const unsigned int SCREEN_HEIGHT;
    static const unsigned int SCREEN_ADDRESS;
    static const unsigned int SERIAL_BAUD_RATE;
    static const arduino::String VERSION;

    static unsigned int CURRENT_STATE;
    static unsigned int PREVIOUS_STATE;

    static const unsigned int UP_BUT;
    static const unsigned int DN_BUT;
    static const unsigned int SL_BUT;
    static const unsigned int BK_BUT;
    static const unsigned int TG_BUT;

    static const unsigned int MM_CUR_X;
    static const unsigned int MM_CUR_Y;
    static const unsigned int MM_MAX_SELECT;

    static const unsigned int DEFAULT_CUR_X;
    static const unsigned int DEFAULT_CUR_Y;

    static const unsigned int CUR_R;
    static const unsigned int CUR_GAP;
};