#pragma once

#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
#include <vector>

// SPI Pins для SD-карты
#define SD_MOSI  6
#define SD_MISO  4
#define SD_SCK   5
#define SD_CS    0  // Chip Select

// Инициализация SD-карты
bool sd_init();

// Отображение случайного JPG из корня SD-карты
void sd_display_random_jpg(uint32_t display_time);

// Внешний доступ к списку файлов (для отладки)
extern std::vector<String> jpg_files;