#include <GyverOLED.h>
#include <vector>

#include "SDCardLevel2.hpp"
#include "Cursor.hpp"
#include "Constants.hpp"
#include "Utils.hpp" 
#include "States.hpp"

SDCardLevel2::SDCardLevel2(unsigned int cX, unsigned int cY, unsigned int cR, unsigned int cGap, unsigned int cMaxLines, CursorType cType)
: cursor(cX, cY, cR, cGap, cMaxLines, cType), drawLock(false), cursorLock(false), isOff(false) {}

void SDCardLevel2::update(States &currentState, States &previousState, GyverOLED<SSD1306_128x32> &display, unsigned int &indexOfDirL2)
{
    if (!this->isOff)
    {
        if (digitalRead(Constants::PIN_UP) == LOW)
        {
            this->cursor.moveUp();
            this->drawLock = false;
            delay(100);
        }

        else if (digitalRead(Constants::PIN_DOWN) == LOW)
        {
            this->cursor.moveDown();
            this->drawLock = false;
            delay(100);
        }

        if (digitalRead(Constants::PIN_SELECT) == LOW && !this->cursorLock)
        {
            indexOfDirL2 = this->cursor.getSelected();
            currentState = States::SDCardLevel3;
            previousState = States::SDCardLevel2;
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
            currentState = States::SDCardMenu;
            previousState = States::MainMenu;
            this->cursor.reset(1, 0);
            this->drawLock = false;
            this->cursorLock = false;
        }
        delay(100);
    }

    
}

void SDCardLevel2::draw(GyverOLED<SSD1306_128x32> &display, std::vector<String> &dirNames, std::vector<String> &dirNamesL2, unsigned int &indexOfDir)
{
    if (!this->drawLock)
    {   
        String rootDir = dirNames[indexOfDir];

        dirNamesL2 = Utils::SDGetDirNames(rootDir);

        if (dirNamesL2.size() > 0)
            this->cursor.setMaxSelect(dirNamesL2.size());
        else
        {
            this->cursorLock = true;
            this->cursor.setMaxSelect(Constants::DISPLAY_MAX_LINES);
        }

        Utils::clearDisplay(display);

        if (!this->cursorLock)
            this->cursor.draw(display);

        std::vector<String> lines;

        if (dirNamesL2.size() == 1)
            lines.push_back(dirNamesL2[this->cursor.getPage() - 1]);
        
        else if (dirNamesL2.size() == 2)
        {
            lines.push_back(dirNamesL2[this->cursor.getPage() - 1]);
            lines.push_back(dirNamesL2[this->cursor.getPage()]);
        }

        else if (dirNamesL2.size() == 3)
        {
            lines.push_back(dirNamesL2[this->cursor.getPage() - 1]);
            lines.push_back(dirNamesL2[this->cursor.getPage()]);
            lines.push_back(dirNamesL2[this->cursor.getPage() + 1]);
        }

        else if (dirNamesL2.size() >= 4)
        {
            lines.push_back(dirNamesL2[this->cursor.getPage() - 1]);
            lines.push_back(dirNamesL2[this->cursor.getPage()]);
            lines.push_back(dirNamesL2[this->cursor.getPage() + 1]);
            lines.push_back(dirNamesL2[this->cursor.getPage() + 2]);
        }
        else
        {
            lines.push_back("There are no");
            lines.push_back("directories to open.");
        }
        

        for (auto s : lines)
        {
            display.println(s);
        }

        display.update();

        this->drawLock = true;

    }
}