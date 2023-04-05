#include <GyverOLED.h>
#include <vector>
#include <random>

#include "Constants.hpp"
#include "Snake/Fruit.hpp"
#include "Snake/Snake.hpp"

Fruit::Fruit(Snake &snake, unsigned int cellSpacing)
: fruitRect(Vector2i(0, 0), cellSpacing, cellSpacing), snake(&snake), rng(this->dev()), dist(0, ((Constants::DISPLAY_WIDTH / cellSpacing) * (Constants::DISPLAY_HEIGHT / cellSpacing)) - 1)
{
    int fruitX = 0;
    int fruitY = 0;

    for (unsigned int x = 0; x < Constants::DISPLAY_WIDTH / cellSpacing; ++x)
    {
        for (unsigned int y = 0; y < Constants::DISPLAY_HEIGHT / cellSpacing; ++y)
        {
            this->possiblePos.push_back(Vector2i(fruitX, fruitY));
            fruitY += cellSpacing;
        }
        fruitX += cellSpacing;
        fruitY = 0;
    }

    this->fruitRect.setPos(this->possiblePos[this->dist(this->rng)]);
}

void Fruit::update()
{
    if (this->snake->detectFruitCollision(this->fruitRect))
        this->fruitRect.setPos(this->possiblePos[this->dist(this->rng)]);
}

void Fruit::draw(GyverOLED<SSD1306_128x32> &display)
{
    this->fruitRect.draw(display);
}