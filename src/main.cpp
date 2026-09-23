/*
File: main.cpp
Path:
E:\Platform_Ide_Projects\Button_proj
*/

#include <Arduino.h>
#include <Button.h>
#include <Game.h>

void setup()
{
    buttonBegin();
    initializeGame();
}

void loop()
{
    const uint32_t now = millis();
    const bool buttonWasPressed = checkButtonPress(now);
    gameNew(now, buttonWasPressed);
}
й ё