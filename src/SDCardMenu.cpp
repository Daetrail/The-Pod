#include <GyverOLED.h>
#include <vector>

#include "SDCardMenu.hpp"
#include "Cursor.hpp"
#include "Constants.hpp"
#include "Utils.hpp" 
#include "States.hpp"

SDCardMenu::SDCardMenu(unsigned int cX, unsigned int cY, unsigned int cR, unsigned int cGap, unsigned int cMaxLines, CursorType cType)
: cursor(cX, cY, cR, cGap, cMaxLines, cType), drawLock(false), cursorLock(false), isOff(false) {}

void SDCardMenu::update(States &currentState, States &previousState, GyverOLED<SSD1306_128x32> &display, unsigned int &indexOfDir)
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
            indexOfDir = this->cursor.getSelected();
            currentState = States::SDCardLevel2;
            previousState = States::SDCardMenu;
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
            currentState = States::MainMenu;
            previousState = States::MainMenu;
            this->cursorLock = false;
            this->drawLock = false;
        }
        delay(100);
    }

    
}

void SDCardMenu::draw(GyverOLED<SSD1306_128x32> &display, std::vector<String> &dirNames)
{
    if (!this->drawLock)
    {   
        dirNames = Utils::SDGetDirNames("/");
        if (dirNames.size() > 0)
            this->cursor.setMaxSelect(dirNames.size());
        else
        {
            this->cursorLock = true;
            this->cursor.setMaxSelect(Constants::DISPLAY_MAX_LINES);
        }

        Utils::clearDisplay(display);

        if (!this->cursorLock)
            this->cursor.draw(display);

        std::vector<String> lines;

        if (dirNames.size() == 1)
            lines.push_back(dirNames[this->cursor.getPage() - 1]);
        
        else if (dirNames.size() == 2)
        {
            lines.push_back(dirNames[this->cursor.getPage() - 1]);
            lines.push_back(dirNames[this->cursor.getPage()]);
        }

        else if (dirNames.size() == 3)
        {
            lines.push_back(dirNames[this->cursor.getPage() - 1]);
            lines.push_back(dirNames[this->cursor.getPage()]);
            lines.push_back(dirNames[this->cursor.getPage() + 1]);
        }

        else if (dirNames.size() >= 4)
        {
            lines.push_back(dirNames[this->cursor.getPage() - 1]);
            lines.push_back(dirNames[this->cursor.getPage()]);
            lines.push_back(dirNames[this->cursor.getPage() + 1]);
            lines.push_back(dirNames[this->cursor.getPage() + 2]);
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


