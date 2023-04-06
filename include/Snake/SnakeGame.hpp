#pragma once

#include <GyverOLED.h>

#include "Snake/Snake.hpp"
#include "Snake/Fruit.hpp"
#include "States.hpp"

struct SnakeGameConstants
{
    // Value has to be a factor of both Constants::DISPLAY_WIDTH and Constants::DISPLAY_HEIGHT.
    static const unsigned int DEFAULT_CELL_SPACING;
};

class SnakeGame
{
public:
    SnakeGame(unsigned int cellSpacing, unsigned int frameRate);    

    void update(States &currentState, unsigned int deltaTime);

    void draw(GyverOLED<SSD1306_128x32> &display);
    
private:
    unsigned int cellSpacing;
    unsigned int frameRate;

    Snake snake;
    Fruit fruit;
};