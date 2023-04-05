#pragma once

#include <GyverOLED.h>

#include "Cursor.hpp"
#include "States.hpp"

class GameMenu
{
public:
    GameMenu(unsigned int cX, unsigned int cY, unsigned int cR, unsigned int cGap, unsigned int cMaxLines, CursorType cType);

    void update(States &currentState, States &previousState, GyverOLED<SSD1306_128x32> &display);

    void draw(GyverOLED<SSD1306_128x32> &display);

private:
    Cursor cursor;

    bool isOff;
    bool drawLock;
};
