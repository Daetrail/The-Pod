#pragma once

#include <GyverOLED.h>

struct Vector2i
{
    Vector2i(int x, int y);
    Vector2i();
    Vector2i operator* (int direction);
    Vector2i operator+= (Vector2i vector);
    Vector2i operator+ (Vector2i vector);
    bool operator!= (Vector2i vector);
    bool operator== (Vector2i vector);
    int x, y;
};

class Rect
{
public:
    Rect(Vector2i topLeftCoord, unsigned int width, unsigned int height);

    void move(Vector2i vector);

    void draw(GyverOLED<SSD1306_128x32> &display);

    void setBoundary(int bx, int by, int b2x, int b2y);
    void setPos(Vector2i position);

    Vector2i getPos();

    bool hasCollidedWithRect(Rect &rect);
    bool checkIfRectWillCollide(Vector2i movement, Rect &rect);

private:
    Vector2i topLeftCoord; 

    int width, height;

    bool boundarySet;

    // Boundary limits
    int bx, by, b2x, b2y;
};