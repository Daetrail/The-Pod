#pragma once

#include <GyverOLED.h>

// Passed as an argument to the Cursor class to specify what type is needed for each menu.
enum class CursorType : unsigned int
{
    unlimitedSelection,
    scrolling
};

// Controls the position of the cursor and determines what is selected by the user.
class Cursor 
{
// Constructors
public:
    // Used for a fixed, known number of selections.
    Cursor(unsigned int x, unsigned int y, unsigned int r, unsigned int gap, unsigned int maxLines, unsigned int maxSelect);

    // Used to vary the type of selection, as available in CursorType.
    Cursor(unsigned int x, unsigned int y, unsigned int r, unsigned int gap, unsigned int maxLines, CursorType type);

// Functionality
public:
    void moveUp();
    void moveDown();

    // Resets to specified values for scrolling/unlimited selection cursors.
    void reset(unsigned int page, unsigned int selected);

    void draw(GyverOLED<SSD1306_128x32> &display);

// Getters
public:
    // Returns the index which is currently selected by the user.
    unsigned int getSelected();

    // Returns the page number which the cursor is on.
    unsigned int getPage();

// Setters
public:
    // Sets maximum selections for cursor.
    void setMaxSelect(unsigned int maxSelect);

// Variables
private:
    // Declares the (x, y) coordinates and the r radius.
    unsigned int x, y, r;

    // Declares the spacing between each cursor position.
    unsigned int gap;

    // Declares the maximum select for fixed (and dynamically for unlimited & scrolling types).
    unsigned int maxSelect;

    // Declares the possible number of positions the cursor can be at
    unsigned int maxLines;

    // Stores the y coordinate of the first selection
    unsigned int originalY;

    // Self-explanatory.
    CursorType type;
    bool isFixed;

    // Stores what is selected by the cursor.
    unsigned int currentlySelected;

    // Stores the page the cursor is on.
    unsigned int currentPage;

    // Maximum number of pages
    unsigned int maxPages;

    // Flags to see which direction the cursor should be drawn in next.
    bool hasMovedUp;
    bool hasMovedDown;
};