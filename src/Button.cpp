/*
File: Button.cpp
Path:
E:\Platform_Ide_Projects\Button_proj
*/

#include <Button.h>
#include <Config.h>

namespace
{
    uint8_t rawButtonBefore = HIGH;
    uint8_t stableStateButton = HIGH;
    uint32_t lastTime = 0;
}

void buttonBegin()
{
    pinMode(buttonPin, INPUT_PULLUP);
}

bool checkButtonPress(uint32_t now)
{
    uint8_t rawButtonState = digitalRead(buttonPin);
    if (rawButtonState != rawButtonBefore)
    {
        lastTime = now;
        rawButtonBefore = rawButtonState;
    }
    if ((now - lastTime) >= debounceTimeMs)
    {
        if (stableStateButton != rawButtonState)
        {
            stableStateButton = rawButtonState;
            if (stableStateButton == LOW)
            {
                return true;
            }
        }
    }
    return false;
}