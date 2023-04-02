#pragma once

#include <GyverOLED.h>
#include <vector>

#include "Cursor.hpp"
#include "States.hpp"

class SDCardLevel2
{
public:
    SDCardLevel2(unsigned int cX, unsigned int cY, unsigned int cR, unsigned int cGap, unsigned int cMaxLines, CursorType cType);

    void update(States &currentState, States &previousState, GyverOLED<SSD1306_128x32> &display, unsigned int &indexOfDirL2);

    void draw(GyverOLED<SSD1306_128x32> &display, std::vector<String> &dirNames, std::vector<String> &dirNamesL2, unsigned int &indexOfDir);

private:
    Cursor cursor;

    bool drawLock;
    bool cursorLock;
    bool isOff;
};