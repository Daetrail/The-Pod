#include <GyverOLED.h>

#include "Cursor.hpp"

/* ----========----========----========----========---- */

Cursor::Cursor(unsigned int x, unsigned int y, unsigned int r, unsigned int gap, unsigned int maxLines, unsigned int maxSelect)
: x(x), y(y), r(r), gap(gap), maxLines(maxLines), maxSelect(maxSelect), originalY(y), isFixed(true), currentlySelected(0) {}

Cursor::Cursor(unsigned int x, unsigned int y, unsigned int r, unsigned int gap, unsigned int maxLines, CursorType type)
: x(x), y(y), r(r), gap(gap), maxLines(maxLines), originalY(y), type(type), isFixed(false), currentlySelected(0), currentPage(1) {}

/* ----========----========----========----========---- */

void Cursor::moveUp()
{
    if (this->isFixed)
    {
        if (this->currentlySelected > 0)
        {
            this->y -= this->gap;
            this->currentlySelected--;
            this->hasMovedUp = true;
        }
    }
    else
    {
        if (this->type == CursorType::unlimitedSelection)
        {
            if (this->y > this->originalY)
            {   
                this->y -= this->gap;
                this->currentlySelected--;
                this->hasMovedUp = true;
            }
            else
            {
                if (this->currentPage != 1)
                {
                    this->currentPage--;
                    this->currentlySelected--;
                }
                else if (this->maxPages != 1)
                {
                    this->currentPage = this->maxPages;
                    this->y = this->originalY + this->gap * (this->maxLines - 1);
                    this->currentlySelected = this->maxSelect - 1;
                }
            }
        }
        else
        {
            if (this->currentPage != 1)
                this->currentPage--;
            else
                this->currentPage = this->maxPages;
        }
    }
}

void Cursor::moveDown()
{
    if (this->isFixed)
    {
        if (this->currentlySelected < this->maxSelect - 1)
        {
            this->y += this->gap;
            this->currentlySelected++;
            this->hasMovedDown = true;
        }
    }
    else
    {
        if (this->type == CursorType::unlimitedSelection)
        {
            if (this->maxSelect <= this->maxLines)
            {
                if (this->currentlySelected < this->maxSelect - 1)
                {
                    this->y += this->gap;
                    this->currentlySelected++;
                    this->hasMovedDown = true;
                }
            }
            else if (this->currentPage < this->maxPages)
            {   
                // Only executes if cursor is in the maxLines - 1 position on display.
                if (this->y < this->originalY + (this->gap * (this->maxLines - 1)))
                {
                    this->y += this->gap;
                    this->currentlySelected++;
                    this->hasMovedDown = true;
                }
                else
                {
                    this->currentlySelected++;
                    this->currentPage++;
                }
            }
            else if (this->currentlySelected < this->maxSelect && this->y < this->originalY + (this->gap * (this->maxLines - 1)))
            {
                this->y += this->gap;
                this->currentlySelected++;
                this->hasMovedDown = true;
            }
            else
            {
                this->currentPage = 1;
                this->y = this->originalY;
                this->currentlySelected = 0;
            }
        }
        else
        {
            if (this->currentPage < this->maxPages)
                this->currentPage++;
            else
                this->currentPage = 1;
        }
    }
}

void Cursor::reset(unsigned int page, unsigned int selected)
{
    this->y = this->originalY;
    this->currentPage = page;
    this->currentlySelected = selected;
}

void Cursor::draw(GyverOLED<SSD1306_128x32> &display)
{
    if (this->hasMovedUp)
    {
        display.circle(this->x, this->y + this->gap, this->r, OLED_CLEAR);
        this->hasMovedUp = false;
    }
    if (this->hasMovedDown)
    {
        display.circle(this->x, this->y - this->gap, this->r, OLED_CLEAR);
        this->hasMovedDown = false;
    }
    display.circle(this->x, this->y, this->r, OLED_FILL);
}

/* ----========----========----========----========---- */

unsigned int Cursor::getSelected()
{
    return this->currentlySelected;
}

unsigned int Cursor::getPage()
{
    return this->currentPage;
}

/* ----========----========----========----========---- */

void Cursor::setMaxSelect(unsigned int maxSelect)
{
    this->maxSelect = maxSelect;

    // Selections = n, Pages = (n - (maxLines - 1)), only when n > maxLines
    if (this->maxSelect <= this->maxLines)
        this->maxPages = 1;
    else
        this->maxPages = maxSelect - (this->maxLines - 1);
}

/* ----========----========----========----========---- */


