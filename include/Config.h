/*
File: Config.h
Path:
E:\Platform_Ide_Projects\Button_proj
*/

#pragma once
#include <Arduino.h>

constexpr uint8_t ledPin = LED_BUILTIN;
constexpr uint8_t buttonPin = 2;
constexpr uint8_t ringPin = 7;

constexpr uint32_t debounceTimeMs = 30;
constexpr uint32_t allRingTimeMs = 5000;
constexpr uint32_t resultAllRingTimeMs = 1000;

constexpr uint8_t ringBrightness = 1;
constexpr uint16_t pixelNumber = 90;
constexpr uint32_t timeToWinMs = 1000;