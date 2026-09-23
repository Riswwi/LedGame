/*
File: Game.cpp
Path:
E:\Platform_Ide_Projects\Button_proj
*/

#include <Game.h>
#include <Adafruit_NeoPixel.h>
#include <Config.h>

namespace
{
    enum class GameState : uint8_t
    {
        Waiting,
        Glowing,
        Target,
        Win,
        Lose
    };
    GameState currentGameState = GameState::Waiting;
    Adafruit_NeoPixel ring(pixelNumber, ringPin, NEO_GRB | NEO_KHZ800);
    uint32_t stateStartTime = 0;
}

void initializeGame()
{
    ring.begin();
    ring.setBrightness(ringBrightness);
    ring.clear();
    ring.setPixelColor(0, ring.Color(255, 0, 0));
    ring.show();
}
void gameNew(uint32_t now, bool buttonWasPressed)
{
    switch (currentGameState)
    {
    case GameState::Waiting:
        if (buttonWasPressed)
        {
            ring.clear();
            ring.show();
            stateStartTime = now;
            currentGameState = GameState::Glowing;
        }
        break;

    case GameState::Glowing:
    {
        const uint32_t expiredTime = now - stateStartTime;
        if (buttonWasPressed)
        {
            currentGameState = GameState::Lose;
            stateStartTime = now;
            break;
        }
        const uint16_t glowingPixelCount = (expiredTime * pixelNumber) / allRingTimeMs;
        if (expiredTime >= allRingTimeMs)
        {
            ring.fill(ring.Color(255, 0, 0));
            ring.show();
            stateStartTime = now;
            currentGameState = GameState::Target;
        }
        else
        {
            ring.clear();

            for (uint16_t pixelIndex = 0; pixelIndex < glowingPixelCount; ++pixelIndex)
            {
                ring.setPixelColor(pixelIndex, ring.Color(255, 0, 0));
            }

            ring.show();
        }
        break;
    }

    case GameState::Target:
    {
        const uint32_t targetExpiredTime = now - stateStartTime;
        if (targetExpiredTime >= timeToWinMs)
        {
            currentGameState = GameState::Lose;
            stateStartTime = now;
        }
        else if (buttonWasPressed)
        {
            currentGameState = GameState::Win;
            stateStartTime = now;
            break;
        }
        break;
    }
    case GameState::Win:
        ring.fill(ring.Color(0, 255, 0));
        ring.show();
        if ((now - stateStartTime) >= resultAllRingTimeMs)
        {
            ring.clear();
            ring.show();
            currentGameState = GameState::Waiting;
        }
        break;

    case GameState::Lose:
        ring.fill(ring.Color(255, 0, 0));
        ring.show();
        if ((now - stateStartTime) >= resultAllRingTimeMs)
        {
            ring.clear();
            ring.show();
            currentGameState = GameState::Waiting;
        }
        break;
    }
}