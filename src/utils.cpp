#include <GyverOLED.h>
#include <Wire.h>
#include <LittleFS.h>
#include <vector>
#include <SDFS.h>
#include <SPI.h>

#include "Utils.hpp"
#include "Constants.hpp"

void Utils::initDisplay(GyverOLED<SSD1306_128x32> &display)
{
    display.init();
    display.clear();
    display.home();
    display.setScale(1);    
    display.invertText(false);
}

void Utils::clearDisplay(GyverOLED<SSD1306_128x32> &display)
{
    display.clear();
    display.home();
}

void Utils::initButtons()
{
    pinMode(Constants::PIN_UP, INPUT_PULLUP);
    pinMode(Constants::PIN_DOWN, INPUT_PULLUP);
    pinMode(Constants::PIN_SELECT, INPUT_PULLUP);
    pinMode(Constants::PIN_BACK, INPUT_PULLUP);
    pinMode(Constants::PIN_OFF, INPUT_PULLUP);
}

void Utils::setI2CPins(unsigned int sda, unsigned int scl)
{
    Wire.setSDA(sda);
    Wire.setSCL(scl);
}

void Utils::setSPIPins(unsigned int tx, unsigned int rx, unsigned int cs, unsigned int clk)
{
    SPI.setTX(tx);
    SPI.setRX(rx);
    SPI.setCS(cs);
    SPI.setSCK(clk);
}

std::vector<String> Utils::SDGetDirNames(String directory)
{
    Dir dir = SDFS.openDir(directory);
    std::vector<String> dirNames;


    while (dir.next())
    {   
        if (dir.isDirectory())
        {   
            if (dir.fileName() == "System Volume Information")
                continue;
            dirNames.push_back("/" + dir.fileName());
        }
    }

    return dirNames;
}

std::vector<String> Utils::getFileNames(String directory, bool onSd)
{   
    Dir dir;
    if (!onSd)
        dir = LittleFS.openDir(directory);
    else
        dir = SDFS.openDir(directory);


    std::vector<String> fileNames;

    while (dir.next())
    {
        fileNames.push_back(dir.fileName());
    }

    return fileNames;
}

unsigned int Utils::getTotalLinesFromFile(String fullFileName, bool onSd)
{
    File file;
    if (!onSd)
        file = LittleFS.open(fullFileName, "r");
    else
        file = SDFS.open(fullFileName, "r");


    unsigned int counter = 0;
    while (file.available())
    {
        file.readStringUntil('\n');
        counter++;
    }

    file.close();
    return counter;
}

std::array<String, 4> Utils::getDataFromFile(String fullFileName, unsigned int pageNum, bool onSd)
{  
    File file;
    if (!onSd)
        file = LittleFS.open(fullFileName, "r");
    else
        file = SDFS.open(fullFileName, "r");


    std::array<String, 4> data;

    for (unsigned int i = 0; i < Constants::DISPLAY_MAX_LINES; i++)
    {
        if (pageNum - 1 > 0)
        {
            pageNum--;
            i--;
            file.readStringUntil('\n');
            continue;
        }
        data[i] = file.readStringUntil('\n');
    }

    file.close();

    return data;
}