#pragma once

#include <GyverOLED.h>
#include <vector>

#include "Cursor.hpp"
#include "States.hpp"

class FlashMenu
{
public:
    FlashMenu(unsigned int cX, unsigned int cY, unsigned int cR, unsigned int cGap, unsigned int cMaxLines, CursorType cType);

    void update(States &currentState, States &previousState, GyverOLED<SSD1306_128x32> &display, unsigned int &indexOfFile, String &fileDirectory, bool &onSd);

    void draw(GyverOLED<SSD1306_128x32> &display, std::vector<String> &fileNames);
    
private:
    Cursor cursor;
    bool drawLock;
    bool cursorLock;
    bool isOff;
};

