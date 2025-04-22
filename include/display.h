#pragma once

#include <Arduino.h>
#include <LovyanGFX_Driver.h>
#include <TCA9534.h>

extern TCA9534 ioex;
extern LGFX gfx;

void display_init();