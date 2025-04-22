#pragma once

#include <TAMC_GT911.h>
#include <lvgl.h>

// Инициализация тачскрина
void touch_init();

// Функция чтения тачскрина для LVGL
void touchpad_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data);