#include <GyverOLED.h>
#include <vector>

#include "SDCardLevel3.hpp"
#include "Cursor.hpp"
#include "Constants.hpp"
#include "Utils.hpp" 
#include "States.hpp"

SDCardLevel3::SDCardLevel3(unsigned int cX, unsigned int cY, unsigned int cR, unsigned int cGap, unsigned int cMaxLines, CursorType cType)
: cursor(cX, cY, cR, cGap, cMaxLines, cType), drawLock(false), cursorLock(false), isOff(false) {}

void SDCardLevel3::update(States &currentState, States &previousState, GyverOLED<SSD1306_128x32> &display, unsigned int &indexOfFile, bool &onSd)
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
            indexOfFile = this->cursor.getSelected();
            currentState = States::ViewDoc;
            previousState = States::SDCardLevel3;
            onSd = true;
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
            currentState = States::SDCardLevel2;
            previousState = States::SDCardMenu;
            this->cursor.reset(1, 0);
            this->drawLock = false;
            this->cursorLock = false;
        }
        delay(100);
    }

    
}

void SDCardLevel3::draw(GyverOLED<SSD1306_128x32> &display, std::vector<String> &fileNames, std::vector<String> &dirNames, std::vector<String> &dirNamesL2, unsigned int &indexOfDir, unsigned int &indexOfDirL2)
{
    if (!this->drawLock)
    {   
        String rootDir = dirNames[indexOfDir];

        String relativeDir = dirNamesL2[indexOfDirL2];

        String fullDir = rootDir + relativeDir;

        fileNames = Utils::getFileNames(fullDir, true);

        if (fileNames.size() > 0)
            this->cursor.setMaxSelect(fileNames.size());
        else
        {
            this->cursorLock = true;
            this->cursor.setMaxSelect(Constants::DISPLAY_MAX_LINES);
        }

        Utils::clearDisplay(display);

        if (!this->cursorLock)
            this->cursor.draw(display);

        std::vector<String> lines;

        if (fileNames.size() == 1)
            lines.push_back(fileNames[this->cursor.getPage() - 1]);
        
        else if (fileNames.size() == 2)
        {
            lines.push_back(fileNames[this->cursor.getPage() - 1]);
            lines.push_back(fileNames[this->cursor.getPage()]);
        }

        else if (fileNames.size() == 3)
        {
            lines.push_back(fileNames[this->cursor.getPage() - 1]);
            lines.push_back(fileNames[this->cursor.getPage()]);
            lines.push_back(fileNames[this->cursor.getPage() + 1]);
        }

        else if (fileNames.size() >= 4)
        {
            lines.push_back(fileNames[this->cursor.getPage() - 1]);
            lines.push_back(fileNames[this->cursor.getPage()]);
            lines.push_back(fileNames[this->cursor.getPage() + 1]);
            lines.push_back(fileNames[this->cursor.getPage() + 2]);
        }
        else
        {
            lines.push_back("There are no files");
            lines.push_back("to open.");
        }
        
        // Serial.println(String(this->cursor.getPage()) + " " + String(this->cursor.getSelected()));
        // Serial.println(String(this->cursor.getPage()) + " " + String(this->cursor.getSelected()));

        for (auto s : lines)
        {
            display.println(s);
        }

        display.update();

        this->drawLock = true;
    }
}