#pragma once

#include <Arduino.h>
#include <lvgl.h>

// Инициализация UI
void ui_init();

// Получение текущего режима (0: Оффлайн, 1: Онлайн)
int get_current_mode();