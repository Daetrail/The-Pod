#pragma once

#include <GyverOLED.h>
#include <LittleFS.h>

#include "Cursor.hpp"
#include "States.hpp"

class ViewDoc
{
public:
    ViewDoc(unsigned int cX, unsigned int cY, unsigned int cR, unsigned int cGap, unsigned int cMaxLines, CursorType cType);

    void update(States &currentState, States &previousState, GyverOLED<SSD1306_128x32> &display);

    void draw(GyverOLED<SSD1306_128x32> &display, String fileName, bool onSd);

private:
    Cursor cursor;
    bool drawLock;
    bool isOff;
    bool alreadyCalculatedTotalLines;

    unsigned int totalLines;
    
};