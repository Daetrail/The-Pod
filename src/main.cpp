#include <Arduino.h>
#include <GyverOLED.h>
#include <Wire.h>
#include <LittleFS.h>

#include "globals.hpp"
#include "utils.hpp"

GyverOLED<SSD1306_128x32> oled(Global::SCREEN_ADDRESS);

bool tgLock = false;
bool drawLock = false;
bool curLock = false;
unsigned int optionSelected;

utils::Cursor cursor(Global::CUR_R, Global::MM_CUR_X, Global::MM_CUR_Y, Global::MM_MAX_SELECT);
utils::DataHandler data;

void setup()
{
    Wire.setSDA(Global::PIN_DISPLAY_SDA);
    Wire.setSCL(Global::PIN_DISPLAY_SCL);

    Serial.begin(Global::SERIAL_BAUD_RATE);

    LittleFS.begin();

    utils::initButtons();
    utils::initScreen(oled);
}

void loop()
{
    if (!drawLock)
    {
        switch (Global::CURRENT_STATE)
        {
        case STATES::MainMenu:
            cursor.setMaxSelect(Global::MM_MAX_SELECT);
            cursor.setPos(Global::MM_CUR_X, Global::MM_CUR_Y);
            utils::clear(oled);
            utils::drawMenu(oled);
            oled.update();
            break;
        case STATES::FlashMenu:
            cursor.setPos(Global::DEFAULT_CUR_X, Global::DEFAULT_CUR_Y);
            curLock = false;
            utils::clear(oled);
            utils::drawFlashMenu(oled, data, cursor);
            oled.update();
            break;
        case STATES::SDCardMenu:
            utils::clear(oled);
            utils::drawSDCardMenu(oled);
            oled.update();
            break;
        case STATES::ViewFlashDocs:
            utils::clear(oled);
            utils::drawViewFlashDocs(oled, data, cursor, optionSelected);
            oled.update();
            break;
        case STATES::Off:
            utils::clear(oled);
            break;
        }
        drawLock = true;
    }

    switch (Global::CURRENT_STATE)
    {
    case STATES::MainMenu:
        optionSelected = cursor.getSelected();
        if (digitalRead(Global::SL_BUT) == LOW && optionSelected == MM_SELECT::Flash)
        {
            Global::CURRENT_STATE = STATES::FlashMenu;
            Global::PREVIOUS_STATE = STATES::MainMenu;
            drawLock = false;
            delay(100);
        }
        if (digitalRead(Global::SL_BUT) == LOW && optionSelected == MM_SELECT::SDCard)
        {
            Global::CURRENT_STATE = STATES::SDCardMenu;
            Global::PREVIOUS_STATE = STATES::MainMenu;
            drawLock = false;
            delay(100);
        }
        break;
    case STATES::FlashMenu:
        optionSelected = cursor.getSelected();
        if (digitalRead(Global::SL_BUT) == LOW)
        {
            Global::CURRENT_STATE = STATES::ViewFlashDocs;
            Global::PREVIOUS_STATE = STATES::FlashMenu;
            drawLock = false;
            delay(100);
        }
        break;
    case STATES::ViewFlashDocs:
        curLock = true;
        break;
    case STATES::SDCardMenu:
        curLock = true;
        break;
    }

    if (!curLock)
    {
        cursor.draw(oled);
        oled.update();
        curLock = true;
    }

    if (digitalRead(Global::UP_BUT) == LOW)
    {
        cursor.moveUp();
        curLock = false;
        delay(100);
    }

    if (digitalRead(Global::DN_BUT) == LOW)
    {
        cursor.moveDown();
        curLock = false;
        delay(100);
    }

    if (digitalRead(Global::TG_BUT) == LOW && !tgLock)
    {
        Global::PREVIOUS_STATE = Global::CURRENT_STATE;
        Global::CURRENT_STATE = STATES::Off;
        tgLock = true;
        drawLock = false;
        delay(100);
    }

    if (digitalRead(Global::BK_BUT) == LOW)
    {
        if (Global::CURRENT_STATE != STATES::MainMenu)
        {
            Global::CURRENT_STATE = Global::PREVIOUS_STATE;
            if (Global::CURRENT_STATE == STATES::FlashMenu || Global::CURRENT_STATE == STATES::SDCardMenu)
                Global::PREVIOUS_STATE = STATES::MainMenu;
            if (Global::CURRENT_STATE == STATES::ViewFlashDocs)
                Global::PREVIOUS_STATE = STATES::FlashMenu;
            drawLock = false;
            tgLock = false;
            curLock = false;
            delay(100);
        }
    }
}
