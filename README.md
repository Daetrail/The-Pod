# The Pod

A little device made for cheating in exams and class tests! You can upload files to an SD card, connect it to your Raspberry Pi Pico and have your documents display for you.

## Concept

The primary idea behind this subject was to:

- Replace the solar panel in a calculator with a display.
- Hijack the buttons in the calculator in order to control the device.
- Install a small battery and an SD card reader to power the device and store data for it.

A button to quickly toggle the device's screen was implemented, in order to avoid detection by exam invigilators or teachers.

## To create a document:

Write your document normally with a .txt file extension preferably
Keep the name of your file short and concise, to ensure it fits within one line on the display.

Afterwards, use the textformatter.py utility provided on it.

Syntax:

```
python textformatter.py <path-to-txt-file>
```

The SD Card must have a certain file structure and format.

Format it to FAT32 first, then create folders as instructed below:

- The root directory of your SD card must all be folders, no text files.
- The 2nd layer (directories inside of the folders in the root directory) must all be folders as well.

Inside the 2nd layer, you can add your text files. 

## To replicate the device:

The components needed are:

- A Raspberry Pi Pico.
- An SD card breakout board.
- An SD Card (to guarantee functionality, please use an 8GB one or less.)
- A SSD1306 128x32 display.
- Wires to connect everything up

Connect the components to the Raspberry Pi Pico as defined in src/Constants.hpp and src/Constants.cpp.

https://datasheets.raspberrypi.com/pico/Pico-R3-A4-Pinout.pdf

Use the pinout diagram above to help you.

