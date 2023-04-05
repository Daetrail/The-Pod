#include <GyverOLED.h>

#include "GameMenu.hpp"
#include "Cursor.hpp"
#include "States.hpp"
#include "Constants.hpp"
#include "Utils.hpp"

GameMenu::GameMenu(unsigned int cX, unsigned int cY, unsigned int cR, unsigned int cGap, unsigned int cMaxLines, CursorType cType)
: cursor(cX, cY, cR, cGap, cMaxLines, cType), isOff(false), drawLock(false)
{}

void GameMenu::update(States &currentState, States &previousState, GyverOLED<SSD1306_128x32> &display)
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

        if (digitalRead(Constants::PIN_SELECT) == LOW)
        {
            if (Constants::GAMES_AVAILABLE[this->cursor.getSelected()] == "Snake")
            {
                currentState = States::GameSnake;
                previousState = States::GameMenu;
                this->drawLock = false;
            }
            else if (Constants::GAMES_AVAILABLE[this->cursor.getSelected()] == "Pong")
            {
                // currentState = States::GamePong;
                // previousState = States::GameMenu;
                // this->drawLock = false;
            }
            else if (Constants::GAMES_AVAILABLE[this->cursor.getSelected()] == "Space Invaders")
            {
                // currentState = States::GameSpaceInvaders;
                // previousState = States::GameMenu;
                // this->drawLock = false;
            }
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
            this->drawLock = false;
        }
        delay(100);
    }
}

void GameMenu::draw(GyverOLED<SSD1306_128x32> &display)
{
    if (!this->drawLock)
    {
        this->cursor.setMaxSelect(Constants::GAMES_AVAILABLE.size());

        Utils::clearDisplay(display);

        this->cursor.draw(display);

        for (unsigned int i = 0; i < Constants::GAMES_AVAILABLE.size(); i++)
        {
            display.println(Constants::GAMES_AVAILABLE[i]);
        }

        display.update();
        
        this->drawLock = true;
    }
}