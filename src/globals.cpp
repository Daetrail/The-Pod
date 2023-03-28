#include "globals.hpp"

const unsigned int Global::PIN_DISPLAY_SDA = 16;
const unsigned int Global::PIN_DISPLAY_SCL = 17;
const unsigned int Global::SCREEN_WIDTH = 128;
const unsigned int Global::SCREEN_HEIGHT = 32;
const unsigned int Global::SCREEN_ADDRESS = 0x3C;
const unsigned int Global::SERIAL_BAUD_RATE = 115200;
const arduino::String Global::VERSION = "BETAv1";

unsigned int Global::CURRENT_STATE = 1;
unsigned int Global::PREVIOUS_STATE = 1;

const unsigned int Global::UP_BUT = 8;
const unsigned int Global::DN_BUT = 10;
const unsigned int Global::SL_BUT = 13;
const unsigned int Global::BK_BUT = 15;
const unsigned int Global::TG_BUT = 2;

const unsigned int Global::MM_CUR_X = 55;
const unsigned int Global::MM_CUR_Y = 12;
const unsigned int Global::MM_MAX_SELECT = 2;

const unsigned int Global::DEFAULT_CUR_X = 120;
const unsigned int Global::DEFAULT_CUR_Y = 5;

const unsigned int Global::CUR_R = 1;
const unsigned int Global::CUR_GAP = 8;