#pragma once

#include <GyverOLED.h>
#include <vector>
#include <random>

#include "Game/Rect.hpp"
#include "Snake/Snake.hpp"

class Fruit
{
public:
    Fruit(Snake &snake, unsigned int cellSpacing);

    void update();

    void draw(GyverOLED<SSD1306_128x32> &display);

private:
    Rect fruitRect;

    std::vector<Vector2i> possiblePos;

    Vector2i currentPos;

    Snake* snake;

    std::random_device dev;
    std::mt19937 rng;
    std::uniform_int_distribution<std::mt19937::result_type> dist;
};

