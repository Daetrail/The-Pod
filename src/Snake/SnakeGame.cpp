#include <GyverOLED.h>

#include "Game/Rect.hpp"
#include "Constants.hpp"
#include "States.hpp"
#include "Utils.hpp"
#include "Snake/SnakeGame.hpp"

const unsigned int SnakeGameConstants::DEFAULT_CELL_SPACING = 4;

SnakeGame::SnakeGame(unsigned int cellSpacing, unsigned int frameRate)
: cellSpacing(cellSpacing), frameRate(frameRate), snake(this->cellSpacing, Vector2i(62, 14), 40), fruit(this->snake, this->cellSpacing)
{
}

void SnakeGame::update(States &currentState, unsigned int deltaTime)
{
    if (digitalRead(Constants::PIN_OFF) == LOW)
    {
        currentState = States::GameMenu;
        delay(150);
    }
    else 
    {
        this->fruit.update();
        this->snake.update(deltaTime);
    }
}

void SnakeGame::draw(GyverOLED<SSD1306_128x32> &display)
{
    Utils::clearDisplay(display);
    this->fruit.draw(display);
    this->snake.draw(display);
    display.update();
}
