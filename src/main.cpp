#include <GyverOLED.h>
#include <LittleFS.h>
#include <vector>
#include <SDFS.h>
#include <SD.h>

#include "States.hpp"
#include "Constants.hpp"
#include "Utils.hpp"

#include "MainMenu.hpp"
#include "FlashMenu.hpp"
#include "ViewDoc.hpp"
#include "SDCardMenu.hpp"
#include "SDCardLevel2.hpp"
#include "SDCardLevel3.hpp"

/* ----========----========----========----========---- */

// Display
GyverOLED<SSD1306_128x32> display(Constants::DISPLAY_ADDRESS);

// States
States currentState = States::MainMenu;
States previousState = States::MainMenu;

// Vector containing file names in FlashMenu and SDCardLevel3 states.
std::vector<String> fileNames;

// Vector containing the directory names for SDCardMenu state.
std::vector<String> dirNames;

// Vector containing the directory names for SDCardLevel2 state;
std::vector<String> dirNamesL2;

// Stores the index of the file in fileNames to be opened.
unsigned int indexOfFile;

// Stores the index of the directory in dirNames to be opened.
unsigned int indexOfDir;

// Stores the index of the directory in dirNamesL2 to be opened.
unsigned int indexOfDirL2;

// If the file being opened derives from FlashMenu or SDCardLevel3.
bool onSd;

// Stores the directory the file being opened is in.
String fileDirectory;

// File to be opened and read.
String currentFileName;

// Main menu
MainMenu mainMenu(Constants::MM_CURSOR_X, Constants::MM_CURSOR_Y, Constants::DEFAULT_CURSOR_R, Constants::CURSOR_GAP, Constants::DISPLAY_MAX_LINES, Constants::MM_MAX_SELECT);

// Flash menu
FlashMenu flashMenu(Constants::DEFAULT_CURSOR_X, Constants::DEFAULT_CURSOR_Y, Constants::DEFAULT_CURSOR_R, Constants::CURSOR_GAP, Constants::DISPLAY_MAX_LINES, CursorType::unlimitedSelection);

// View Doc
ViewDoc viewDoc(Constants::DEFAULT_CURSOR_X, Constants::DEFAULT_CURSOR_Y, Constants::DEFAULT_CURSOR_R, Constants::CURSOR_GAP, Constants::DISPLAY_MAX_LINES, CursorType::scrolling);

// SDCardMenu
SDCardMenu sdCardMenu(Constants::DEFAULT_CURSOR_X, Constants::DEFAULT_CURSOR_Y, Constants::DEFAULT_CURSOR_R, Constants::CURSOR_GAP, Constants::DISPLAY_MAX_LINES, CursorType::unlimitedSelection);

// SDCardLevel2
SDCardLevel2 sdCardLevel2(Constants::DEFAULT_CURSOR_X, Constants::DEFAULT_CURSOR_Y, Constants::DEFAULT_CURSOR_R, Constants::CURSOR_GAP, Constants::DISPLAY_MAX_LINES, CursorType::unlimitedSelection);

// SDCardLevel3
SDCardLevel3 sdCardLevel3(Constants::DEFAULT_CURSOR_X, Constants::DEFAULT_CURSOR_Y, Constants::DEFAULT_CURSOR_R, Constants::CURSOR_GAP, Constants::DISPLAY_MAX_LINES, CursorType::unlimitedSelection);

/* ----========----========----========----========---- */

void setup()
{
    // Setup buttons
    Utils::initButtons();

    // Set I2C pins
    Utils::setI2CPins(Constants::PIN_DISPLAY_SDA, Constants::PIN_DISPLAY_SCL);

    // Set SPI pins
    Utils::setSPIPins(Constants::PIN_SPI_TX, Constants::PIN_SPI_RX, Constants::PIN_SPI_CS, Constants::PIN_SPI_CLK);

    // Initialise display.
    Utils::initDisplay(display);

    // Set baud rate of serial connection to the specified baud rate.
    Serial.begin(Constants::SERIAL_BAUD_RATE);

    // Set the CS pin in the SDFS config.
    SDFSConfig config;
    config.setCSPin(Constants::PIN_SPI_CS);
    SDFS.setConfig(config);

    Utils::clearDisplay(display);

    display.println("Mounting FS...");

    display.update();

    bool sd = SDFS.begin();
    bool flash = LittleFS.begin();

    if (!flash && !sd)
    {
        Utils::clearDisplay(display);
        display.println("Failed to mount!:");
        display.println("SD Card & Flash");
        display.println("Ensure SD card is plugged in.");
        display.update();
        for (;;) {}
    }
    else if (!sd)
    {
        Utils::clearDisplay(display);
        display.println("Failed to mount!:");
        display.println("SD Card");
        display.println("SD card plugged in?");
        display.update();
        for (;;) {}
    }
    else if (!flash)
    {
        Utils::clearDisplay(display);
        display.println("Failed to mount!:");
        display.println("Flash");
        display.println("Board may be defected.");
        display.update();
        for (;;) {}
    }

    delay(500);
}

/* ----========----========----========----========---- */

void loop()
{
    switch (currentState)
    {
        case States::MainMenu:
            mainMenu.update(currentState, previousState, display);
            mainMenu.draw(display);
            break;
        case States::FlashMenu:
            flashMenu.draw(display, fileNames);
            flashMenu.update(currentState, previousState, display, indexOfFile, fileDirectory, onSd);
            break;
        case States::ViewDoc:
            if (!onSd)
                currentFileName = fileDirectory + fileNames[indexOfFile];
            else
                currentFileName = dirNames[indexOfDir] + dirNamesL2[indexOfDirL2] + "/" + fileNames[indexOfFile];
            viewDoc.draw(display, currentFileName, onSd);
            viewDoc.update(currentState, previousState, display);
            break;
        case States::SDCardMenu:
            sdCardMenu.draw(display, dirNames);
            sdCardMenu.update(currentState, previousState, display, indexOfDir);
            break;
        case States::SDCardLevel2:
            sdCardLevel2.draw(display, dirNames, dirNamesL2, indexOfDir);
            sdCardLevel2.update(currentState, previousState, display, indexOfDirL2);
            break;
        case States::SDCardLevel3:
            sdCardLevel3.draw(display, fileNames, dirNames, dirNamesL2, indexOfDir, indexOfDirL2);
            sdCardLevel3.update(currentState, previousState, display, indexOfFile, onSd);
            break;
    }
    // Serial.println(String(rp2040.getUsedHeap()) + "/" + String(rp2040.getTotalHeap()));
}

/* ----========----========----========----========---- */
