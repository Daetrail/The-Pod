#include <GyverOLED.h>

#include "Constants.hpp"
#include "Game/Rect.hpp"
#include "Snake/Snake.hpp"

Snake::Snake(unsigned int cellSpacing, Vector2i initialPosition, unsigned int switchTime)
: initialPosition(initialPosition), cellSpacing(cellSpacing), switchTime(switchTime), totalTime(0)
{
    Rect firstBlob(this->initialPosition, this->cellSpacing, this->cellSpacing);

    this->snakeBlobs.push_back(firstBlob);
}

void Snake::determineDirection()
{
    // Controls:           //
    ////////////////////////
    // PIN_UP     = UP    //
    // PIN_DOWN   = DOWN  //
    // PIN_BACK   = LEFT  //
    // PIN_SELECT = RIGHT //
    if (digitalRead(Constants::PIN_BACK) == LOW)
    {
        if (this->direction == Vector2i(0, 0))
            this->direction = Vector2i(-1, 0);
        else if (this->direction != Vector2i(1, 0))
            this->direction = Vector2i(-1, 0);
    }
    else if (digitalRead(Constants::PIN_SELECT) == LOW)
    {
        if (this->direction == Vector2i(0, 0))
            this->direction = Vector2i(1, 0);
        else if (this->direction != Vector2i(-1, 0))
            this->direction = Vector2i(1, 0);
    }
    else if (digitalRead(Constants::PIN_UP) == LOW)
    {
        if (this->direction == Vector2i(0, 0))
            this->direction = Vector2i(0, -1);
        else if (this->direction != Vector2i(0, 1))
            this->direction = Vector2i(0, -1);
    }
    else if (digitalRead(Constants::PIN_DOWN) == LOW)
    {
        if (this->direction == Vector2i(0, 0))
            this->direction = Vector2i(0, 1);
        else if (this->direction != Vector2i(0, -1))
            this->direction = Vector2i(0, 1);
    }
}

void Snake::addBlob()
{
    Rect blob(Vector2i(0, 0), this->cellSpacing, this->cellSpacing);

    if (this->direction == Vector2i(-1, 0))
        blob.setPos(Vector2i(this->snakeBlobs[0].getPos().x + this->cellSpacing + 1, this->snakeBlobs[0].getPos().y));
    else if (this->direction == Vector2i(1, 0))
        blob.setPos(Vector2i(this->snakeBlobs[0].getPos().x - this->cellSpacing - 1, this->snakeBlobs[0].getPos().y));
    else if (this->direction == Vector2i(0, 1))
        blob.setPos(Vector2i(this->snakeBlobs[0].getPos().x, this->snakeBlobs[0].getPos().y - this->cellSpacing - 1));
    else if (this->direction == Vector2i(0, -1))
        blob.setPos(Vector2i(this->snakeBlobs[0].getPos().x, this->snakeBlobs[0].getPos().y + this->cellSpacing + 1));

    this->snakeBlobs.push_back(blob);
}

void Snake::moveBody()
{
    for (unsigned int i = this->snakeBlobs.size() - 1; i > 0; --i)
    {
        this->snakeBlobs[i].setPos(this->snakeBlobs[i - 1].getPos());
    }
}

void Snake::detectBodyCollision()
{
    for (unsigned int i = 1; i < this->snakeBlobs.size(); ++i)
    {
        if (this->snakeBlobs[0].hasCollidedWithRect(this->snakeBlobs[i]))
            this->reset();
    }
}

void Snake::detectBorderCollision()
{
    if (this->snakeBlobs[0].getPos().x > Constants::DISPLAY_WIDTH || this->snakeBlobs[0].getPos().x < 0 || this->snakeBlobs[0].getPos().y > Constants::DISPLAY_HEIGHT || this->snakeBlobs[0].getPos().y < 0)
        this->reset();
}

bool Snake::detectFruitCollision(Rect &fruitRect)
{
    if (this->snakeBlobs[0].hasCollidedWithRect(fruitRect))
    {
        this->addBlob();
        return true;
    }
    return false;
}

void Snake::reset()
{
    this->direction = Vector2i(0, 0);

    this->snakeBlobs.clear();

    Rect firstBlob(this->initialPosition, this->cellSpacing, this->cellSpacing);

    this->snakeBlobs.push_back(firstBlob);
}

void Snake::update(unsigned int deltaTime)
{
    this->determineDirection();

    this->detectBodyCollision();
    this->detectBorderCollision();

    this->totalTime += deltaTime;

    if (digitalRead(Constants::PIN_OFF) == LOW)
    {
        this->addBlob();
        delay(75);
    }

    if (this->totalTime >= this->switchTime)
    {
        this->moveBody();

        this->snakeBlobs[0].move(this->direction * static_cast<int>(this->cellSpacing));

        this->totalTime -= this->switchTime;
    }
        
}

void Snake::draw(GyverOLED<SSD1306_128x32> &display)
{
    for (auto blob : this->snakeBlobs)
        blob.draw(display);
}