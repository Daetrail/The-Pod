#include <GyverOLED.h>

#include "Game/Rect.hpp"

Vector2i::Vector2i(int x, int y)
: x(x), y(y) {}

Vector2i::Vector2i()
: x(0), y(0) {}

Vector2i Vector2i::operator* (int direction)
{
    return Vector2i(this->x * direction, this->y * direction);
}

Vector2i Vector2i::operator+= (Vector2i vector)
{
    this->x += vector.x;
    this->y += vector.y;
    return *this;
}

Vector2i Vector2i::operator+ (Vector2i vector) 
{
    return Vector2i(this->x + vector.x, this->y + vector.y);
}

bool Vector2i::operator!= (Vector2i vector)
{
    if (this->x != vector.x && this->y != vector.y)
        return true;
    else
        return false;
}

bool Vector2i::operator== (Vector2i vector)
{
    if (this->x == vector.x && this->y == vector.y)
        return true;
    else
        return false;
}

Rect::Rect(Vector2i topLeftCoord, unsigned int width, unsigned int height)
: topLeftCoord(topLeftCoord), width(width - 1), height(height - 1), boundarySet(false)
{}

void Rect::move(Vector2i vector)
{
    Vector2i afterChange = this->topLeftCoord + vector;
    if (this->boundarySet && afterChange.x >= this->bx && afterChange.x <= this->b2x && afterChange.y >= this->by && afterChange.y <= b2y)
        this->topLeftCoord += vector;
    else if (!this->boundarySet)        
        this->topLeftCoord += vector;
}

void Rect::draw(GyverOLED<SSD1306_128x32> &display)
{

    display.rect(this->topLeftCoord.x, this->topLeftCoord.y, this->width + this->topLeftCoord.x, this->height + this->topLeftCoord.y, OLED_FILL);
}

void Rect::setBoundary(int bx, int by, int b2x, int b2y)
{
    this->bx = bx;
    this->by = by;
    this->b2x = b2x;
    this->b2y = b2y;
    this->boundarySet = true;
}

void Rect::setPos(Vector2i position)
{
    this->topLeftCoord = position;
}

Vector2i Rect::getPos()
{
    return this->topLeftCoord;
}

bool Rect::hasCollidedWithRect(Rect &rect)
{
    if (this->topLeftCoord.x <= rect.topLeftCoord.x && this->topLeftCoord.x + this->width >= rect.topLeftCoord.x && this->topLeftCoord.y <= rect.topLeftCoord.y && this->topLeftCoord.y + height >= rect.topLeftCoord.y)
    {
        return true;
    }
    
    else if (this->topLeftCoord.x <= rect.topLeftCoord.x + rect.width && this->topLeftCoord.x + this->width >= rect.topLeftCoord.x + rect.width && this->topLeftCoord.y <= rect.topLeftCoord.y && this->topLeftCoord.y + height >= rect.topLeftCoord.y)
    {
        return true;
    }

    else if (this->topLeftCoord.x <= rect.topLeftCoord.x && this->topLeftCoord.x + this->width >= rect.topLeftCoord.x && this->topLeftCoord.y <= rect.topLeftCoord.y + height && this->topLeftCoord.y + height >= rect.topLeftCoord.y + rect.height)
    {
        return true;
    }

    else if (this->topLeftCoord.x <= rect.topLeftCoord.x + rect.width && this->topLeftCoord.x + this->width >= rect.topLeftCoord.x + rect.width && this->topLeftCoord.y <= rect.topLeftCoord.y + rect.height && this->topLeftCoord.y + height >= rect.topLeftCoord.y + rect.height)
    {
        return true;
    }

    else
    {
        return false;
    }    
}

bool Rect::checkIfRectWillCollide(Vector2i movement, Rect &rect)
{
    Vector2i copyCoord = this->topLeftCoord + movement;

    if (copyCoord.x <= rect.topLeftCoord.x && copyCoord.x + this->width >= rect.topLeftCoord.x && copyCoord.y <= rect.topLeftCoord.y && copyCoord.y + this->height >= rect.topLeftCoord.y)
    {
        return true;
    }
    
    else if (copyCoord.x <= rect.topLeftCoord.x + rect.width && copyCoord.x + this->width >= rect.topLeftCoord.x + rect.width && copyCoord.y <= rect.topLeftCoord.y && copyCoord.y + this->height >= rect.topLeftCoord.y)
    {
        return true;
    }

    else if (copyCoord.x <= rect.topLeftCoord.x && copyCoord.x + this->width >= rect.topLeftCoord.x && copyCoord.y <= rect.topLeftCoord.y + height && copyCoord.y + this->height >= rect.topLeftCoord.y + rect.height)
    {
        return true;
    }

    else if (copyCoord.x <= rect.topLeftCoord.x + rect.width && copyCoord.x + this->width >= rect.topLeftCoord.x + rect.width && copyCoord.y <= rect.topLeftCoord.y + rect.height && copyCoord.y + this->height >= rect.topLeftCoord.y + rect.height)
    {
        return true;
    }

    else
    {
        return false;
    }   
}