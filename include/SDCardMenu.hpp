#pragma once

#include <GyverOLED.h>
#include <vector>

#include "Cursor.hpp"
#include "States.hpp"

class SDCardMenu
{
public:
    SDCardMenu(unsigned int cX, unsigned int cY, unsigned int cR, unsigned int cGap, unsigned int cMaxLines, CursorType cType);

    void update(States &currentState, States &previousState, GyverOLED<SSD1306_128x32> &display, unsigned int &indexOfDir);

    void draw(GyverOLED<SSD1306_128x32> &display, std::vector<String> &dirNames);

private:
    Cursor cursor;

    bool drawLock;
    bool cursorLock;
    bool isOff;
};