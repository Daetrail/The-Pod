#pragma once

#include <array>

struct Constants
{
    // Declares the GPIO pin for I2C communication.
    static const unsigned int PIN_DISPLAY_SCL;
    static const unsigned int PIN_DISPLAY_SDA;

    // Declates the SPI0 pins for SD card communication.
    static const unsigned int PIN_SPI_CS;
    static const unsigned int PIN_SPI_CLK;
    static const unsigned int PIN_SPI_TX;
    static const unsigned int PIN_SPI_RX;

    // Address of display in I2C - possibly visible behind the physical SSD1306 128x32 display.
    static const unsigned int DISPLAY_ADDRESS;

    // Baud rate for serial communication with the Raspberry Pi Pico.
    static const unsigned int SERIAL_BAUD_RATE; 

    // GPIO pins of the buttons required.
    static const unsigned int PIN_UP;
    static const unsigned int PIN_DOWN;
    static const unsigned int PIN_SELECT;
    static const unsigned int PIN_BACK;
    static const unsigned int PIN_OFF;

    // Main menu's cursor default coordinates.
    static const unsigned int MM_CURSOR_X;
    static const unsigned int MM_CURSOR_Y;

    // Main menu's maximum select 
    static const unsigned int MM_MAX_SELECT;

    // Every menu's cursor default coordinates and radius except main menu.
    static const unsigned int DEFAULT_CURSOR_X;
    static const unsigned int DEFAULT_CURSOR_Y;
    static const unsigned int DEFAULT_CURSOR_R;

    // Gap between each cursor iteration.
    static const unsigned int CURSOR_GAP;

    // Maximum lines display can show.
    static const unsigned int DISPLAY_MAX_LINES;

    // List of games to play.
    static const std::array<String, 3> GAMES_AVAILABLE;

    // Defines the limits of the display.
    static const unsigned int DISPLAY_WIDTH;
    static const unsigned int DISPLAY_HEIGHT;

    // Defines the maximum FPS for games.
    static const unsigned int FRAME_RATE;
};