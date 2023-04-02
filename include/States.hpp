#pragma once

// Defines the states of the Pod there can be.
enum class States : unsigned int 
{
    MainMenu,
    FlashMenu,
    SDCardMenu,
    ViewDoc,
    SDCardLevel2,
    SDCardLevel3
};

// Defines what can be selected on the main menu.
enum class MainMenuSelection : unsigned int
{
    Flash,
    SDCard
};