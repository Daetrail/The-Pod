#include <GyverOLED.h>
#include <array>
#include <LittleFS.h>

#include "utils.hpp"
#include "globals.hpp"

void utils::initScreen(GyverOLED<SSD1306_128x32> &oled)
{
    oled.init();
    oled.clear();
    oled.update();
    oled.home();
    oled.setScale(1);
    oled.flipV(true);
    oled.flipH(true);
    oled.invertText(false);
    oled.autoPrintln(true);
}

void utils::initButtons()
{
    pinMode(Global::UP_BUT, INPUT_PULLUP);
    pinMode(Global::DN_BUT, INPUT_PULLUP);
    pinMode(Global::SL_BUT, INPUT_PULLUP);
    pinMode(Global::BK_BUT, INPUT_PULLUP);
    pinMode(Global::TG_BUT, INPUT_PULLUP);
}

void utils::clear(GyverOLED<SSD1306_128x32> &oled)
{
    oled.home();
    oled.clear();
    oled.update();
}

void utils::drawMenu(GyverOLED<SSD1306_128x32> &oled)
{
    oled.println("Pod - " + Global::VERSION);
    oled.println("Flash");
    oled.println("SD Card");
}

void utils::drawFlashMenu(GyverOLED<SSD1306_128x32> &oled, utils::DataHandler &data, utils::Cursor &cursor)
{
    std::array<String, 3> dirs = utils::retrieveFileNames("/", 1);
    unsigned int counter = 0;
    for (unsigned int i = 0; i < dirs.size(); i++)
    {
        if (dirs[i].length() != 0)
            counter++;
    }

    cursor.setMaxSelect(counter);

    for (unsigned int i = 0; i < dirs.size(); i++)
    {
        oled.println(dirs[i]);
    }
}

void utils::drawSDCardMenu(GyverOLED<SSD1306_128x32> &oled)
{
    oled.print("SDC Coming soon!");
}

std::array<String, 3> utils::retrieveFileNames(String dirName, unsigned int pageNum)
{
    std::array<String, 3> dirNames;
    Dir dir = LittleFS.openDir(dirName);
    for (unsigned int i = 0; i < 3; i++)
    {
        if (pageNum - 1 > 0)
        {
            pageNum--;
            i--;
            dir.next();
            continue;
        }
        dir.next();
        String dname = dir.fileName();
        dname.replace(".txt", "");
        dirNames[i] = dname;
    }
    return dirNames;
}

utils::Cursor::Cursor(unsigned int r, unsigned int x, unsigned int y, unsigned int maxSelect) : r(r), x(x), y(y), maxSelect(maxSelect), currentSelect(0), hasMovedUp(false), hasMovedDown(false) {}

void utils::Cursor::setPos(unsigned int x, unsigned int y)
{
    this->x = x;
    this->y = y;
}

void utils::Cursor::setMaxSelect(unsigned int maxSelect)
{
    this->maxSelect = maxSelect;
    this->currentSelect = 0;
}

void utils::Cursor::moveUp()
{
    if (this->currentSelect > 0)
    {
        this->y -= Global::CUR_GAP;
        this->currentSelect--;
        this->hasMovedUp = true;
    }
}

void utils::Cursor::moveDown()
{
    if (this->currentSelect < this->maxSelect - 1)
    {
        this->y += Global::CUR_GAP;
        this->currentSelect++;
        this->hasMovedDown = true;
    }
}

unsigned int utils::Cursor::getSelected()
{
    return this->currentSelect;
}

void utils::Cursor::draw(GyverOLED<SSD1306_128x32> &oled)
{
    if (this->hasMovedDown)
    {
        oled.circle(this->x, this->y - Global::CUR_GAP, this->r, OLED_CLEAR);
        this->hasMovedDown = false;
    }
    else if (this->hasMovedUp)
    {
        oled.circle(this->x, this->y + Global::CUR_GAP, this->r, OLED_CLEAR);
        this->hasMovedUp = false;
    }

    oled.circle(this->x, this->y, this->r, OLED_FILL);
}

bool utils::DataHandler::openNewFile(String filename)
{
    if (!LittleFS.exists(filename))
        return false;
    
    this->currentFile = LittleFS.open(filename, "r");
    return true;
}

void utils::DataHandler::closeCurrentFile()
{
    this->currentFile.close();
}

std::array<String, 3> utils::DataHandler::getContents(unsigned int pageNum)
{
    for (unsigned int i = 0; i < 3; i++)
    {
        this->lines[i] = "00-00";
    }
    for (unsigned int i = 0; i < 3 && this->currentFile.available() ; i++)
    {   
        if (pageNum - 1 > 0)
        {
            pageNum--;
            i--;
            this->currentFile.readStringUntil('\n');
            continue;
        }
        this->lines[i] = this->currentFile.readStringUntil('\n');
    }
    
    return this->lines;
}