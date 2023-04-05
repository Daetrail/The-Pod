#include <GyverOLED.h>

#include "MainMenu.hpp"
#include "Cursor.hpp"
#include "Constants.hpp"
#include "States.hpp"
#include "Utils.hpp"

MainMenu::MainMenu(unsigned int cX, unsigned int cY, unsigned int cR, unsigned int cGap, unsigned int cMaxLines, unsigned int cMaxSelect)
: cursor(cX, cY, cR, cGap, cMaxLines, cMaxSelect), drawLock(false), isOff(false) {}

void MainMenu::update(States &currentState, States &previousState, GyverOLED<SSD1306_128x32> &display)
{
    unsigned int optionSelected = this->cursor.getSelected();

    if (!this->isOff)
    {
        if (digitalRead(Constants::PIN_UP) == LOW)
        {
            this->cursor.moveUp();
            this->cursor.draw(display);
            display.update();
            delay(100);
        }
        else if (digitalRead(Constants::PIN_DOWN) == LOW)
        {
            this->cursor.moveDown();
            this->cursor.draw(display);
            display.update();
            delay(100);
        }

        if (digitalRead(Constants::PIN_SELECT) == LOW && optionSelected == static_cast<unsigned int>(MainMenuSelection::Flash))
        {
            previousState = currentState;
            currentState = States::FlashMenu;
            this->drawLock = false;
            delay(100);
        }
        else if (digitalRead(Constants::PIN_SELECT) == LOW && optionSelected == static_cast<unsigned int>(MainMenuSelection::SDCard))
        {
            previousState = currentState;
            currentState = States::SDCardMenu;
            this->drawLock = false;
            delay(100);
        }
        else if (digitalRead(Constants::PIN_SELECT) == LOW && optionSelected == static_cast<unsigned int>(MainMenuSelection::Game))
        {
            previousState = currentState;
            currentState = States::GameMenu;
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
            delay(100);
        }    
    }

}

void MainMenu::draw(GyverOLED<SSD1306_128x32> &display)
{
    if (!this->drawLock)
    {
        Utils::clearDisplay(display);
        display.println("Daetrail's Pod");
        display.println("Flash");
        display.println("SD Card");
        display.println("Games");
        this->cursor.draw(display);
        display.update();
        this->drawLock = true;
    }
}