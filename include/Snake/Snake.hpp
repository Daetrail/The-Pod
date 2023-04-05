#pragma once

#include <GyverOLED.h>
#include <vector>

#include "Game/Rect.hpp"

class Snake
{
public:
    Snake(unsigned int cellSpacing, Vector2i initialPosition, unsigned int switchTime);

    void determineDirection();

    void addBlob();
    void moveBody();

    void detectBodyCollision();
    void detectBorderCollision();
    bool detectFruitCollision(Rect &fruitRect);

    void reset();

    void update(unsigned int deltaTime);
    void draw(GyverOLED<SSD1306_128x32> &display);

private:
    std::vector<Rect> snakeBlobs;

    Vector2i initialPosition;

    unsigned int cellSpacing;

    unsigned int switchTime;
    unsigned int totalTime;

    Vector2i direction;
};