#pragma once

#include <GyverOLED.h>
#include <vector>
#include <array>

#include "Constants.hpp"

namespace Utils
{
    void initDisplay(GyverOLED<SSD1306_128x32> &display);
    void clearDisplay(GyverOLED<SSD1306_128x32> &display);

    void initButtons();
    void setI2CPins(unsigned int sda, unsigned int scl);
    void setSPIPins(unsigned int tx, unsigned int rx, unsigned int cs, unsigned int clk);

    std::vector<String> getFileNames(String directory, bool onSd);

    std::vector<String> SDGetDirNames(String directory);

    unsigned int getTotalLinesFromFile(String fullFileName, bool onSd);

    std::array<String, 4> getDataFromFile(String fullFileName, unsigned int pageNum, bool onSd);
}