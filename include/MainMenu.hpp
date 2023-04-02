#pragma once

#include <GyverOLED.h>

#include "Cursor.hpp"
#include "States.hpp"

class MainMenu
{
public:
    // Constructor which takes in the necessary parameters to pass into the cursor.
    MainMenu(unsigned int cX, unsigned int cY, unsigned int cR, unsigned int cGap, unsigned int cMaxLines, unsigned int cMaxSelect);

    // Detects button presses and controls cursor.
    void update(States &currentState, States &previousState, GyverOLED<SSD1306_128x32> &display);

    // Draws the UI.
    void draw(GyverOLED<SSD1306_128x32> &display);

private:
    Cursor cursor;

    // Renders the UI only once.
    bool drawLock;

    // Stores if display is off or not.
    bool isOff;
};