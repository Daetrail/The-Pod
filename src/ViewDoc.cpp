#include <GyverOLED.h>
#include <LittleFS.h>
#include <array>
#include <ctime>

#include "ViewDoc.hpp"
#include "Cursor.hpp"
#include "States.hpp"
#include "Utils.hpp"
#include "Constants.hpp"

ViewDoc::ViewDoc(unsigned int cX, unsigned int cY, unsigned int cR, unsigned int cGap, unsigned int cMaxLines, CursorType cType)
: cursor(cX, cY, cR, cGap, cMaxLines, CursorType::scrolling), drawLock(false), isOff(false), alreadyCalculatedTotalLines(false) {}

void ViewDoc::update(States &currentState, States &previousState, GyverOLED<SSD1306_128x32> &display)
{
    if (!this->isOff)
    {
        if (digitalRead(Constants::PIN_UP) == LOW)
        {
            this->cursor.moveUp();
            this->drawLock = false;
            delay(100);
        }

        if (digitalRead(Constants::PIN_DOWN) == LOW)
        {
            this->cursor.moveDown();
            this->drawLock = false;
            delay(100);
        }
    }    

    if (digitalRead(Constants::PIN_OFF) == LOW)
    {
        Utils::clearDisplay(display);
        display.update();
        this->isOff = true;
        delay(100);
    }

    if (digitalRead(Constants::PIN_BACK) == LOW)
    {
        if (this->isOff)
        {
            this->isOff = false;
            this->drawLock = false;
        }
        else
        {
            currentState = previousState;
            this->drawLock = false;
            this->alreadyCalculatedTotalLines = false;
            this->cursor.reset(1, 0);
        }
        delay(100);

    }
}

void ViewDoc::draw(GyverOLED<SSD1306_128x32> &display, String fileName, bool onSd)
{
    if (!this->drawLock)
    {
        if (!this->alreadyCalculatedTotalLines)
        {
            Utils::clearDisplay(display);
            
            display.println("Loading...");

            display.update();
            this->totalLines = Utils::getTotalLinesFromFile(fileName, onSd);
            if (this->totalLines != 0)
            {
                this->cursor.setMaxSelect(totalLines);
            }
            else
                this->cursor.setMaxSelect(Constants::DISPLAY_MAX_LINES);
            this->alreadyCalculatedTotalLines = true;
        }

        // std::time_t t = std::time(0);
        std::array<String, 4> data = Utils::getDataFromFile(fileName, this->cursor.getPage(), onSd);
        // std::time_t d = std::time(0);
        // Serial.println("PAGE " + String(this->cursor.getPage()) + ": " + String(static_cast<unsigned int>(d) - static_cast<unsigned int>(t)) + "s");


        if (this->totalLines != 0)
        {
            Utils::clearDisplay(display);
            for (unsigned int i = 0; i < data.size(); i++)
            {   
                display.println(data[i]);
            }
        }
        else
        {
            Utils::clearDisplay(display);
            display.println("File has no data.");
            display.update();
        }
            
        display.update();
        this->drawLock = true;
    }
}