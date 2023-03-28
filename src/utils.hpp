#pragma once
#include <GyverOLED.h>
#include <array>
#include <LittleFS.h>

#include "globals.hpp"

namespace utils
{
    class DataHandler
    {
    public:
        bool openNewFile(String filename);
        void closeCurrentFile();
        std::array<String, 3> getContents(unsigned int pageNum);
    
    private:
        File currentFile;
        std::array<String, 3> lines;
    };

    class Cursor
    {
    public:
        Cursor(unsigned int r, unsigned int x, unsigned int y, unsigned int maxSelect);
        void setPos(unsigned int x, unsigned int y);
        void setMaxSelect(unsigned int maxSelect);
        void moveUp();
        void moveDown();

        unsigned int getSelected();

        void draw(GyverOLED<SSD1306_128x32> &oled);

    private:
        unsigned int r, x, y, maxSelect, currentSelect;
        bool hasMovedUp, hasMovedDown;
    };

    void initScreen(GyverOLED<SSD1306_128x32> &oled);
    void initButtons();

    void clear(GyverOLED<SSD1306_128x32> &oled);

    void drawMenu(GyverOLED<SSD1306_128x32> &oled);
    void drawFlashMenu(GyverOLED<SSD1306_128x32> &oled, DataHandler &data, Cursor &cursor);
    void drawSDCardMenu(GyverOLED<SSD1306_128x32> &oled);

    std::array<String, 3> retrieveFileNames(String dir, unsigned int pageNum);
}