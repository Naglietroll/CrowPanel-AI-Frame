#include "sd_card.h"
#include "display.h"
#include "pins_config.h"
#include <SPI.h>
#include <vector>
#include <random>

SPIClass SD_SPI(HSPI);
std::vector<String> jpg_files;

bool sd_init() {
    Serial.println("[SD] Initializing...");
    SD_SPI.begin(SD_SCK, SD_MISO, SD_MOSI);
    pinMode(SD_CS, OUTPUT);
    digitalWrite(SD_CS, HIGH);

    if (!SD.begin(SD_CS, SD_SPI, 40000000)) {
        Serial.println("[SD] Mount Failed!");
        return false;
    }

    // Поиск JPG-файлов в корне
    File root = SD.open("/");
    if (!root) {
        Serial.println("[SD] Failed to open root!");
        return false;
    }

    File file = root.openNextFile();
    while (file) {
        String filename = file.name();
        if (filename.endsWith(".jpg") || filename.endsWith(".JPG")) {
            // Добавляем "/" к имени файла, если его нет
            if (!filename.startsWith("/")) {
                filename = "/" + filename;
            }
            jpg_files.push_back(filename);
            Serial.printf("[SD] Found: %s\n", filename.c_str());
        }
        file = root.openNextFile();
    }
    root.close();

    if (jpg_files.empty()) {
        Serial.println("[SD] No JPG files found!");
        return false;
    }

    return true;
}

void sd_display_random_jpg(uint32_t display_time) {
    if (jpg_files.empty()) {
        Serial.println("[SD] No files to display!");
        return;
    }

    // Выбор случайного файла
    int idx = random(jpg_files.size());
    String path = jpg_files[idx];
    Serial.printf("[SD] Displaying: %s\n", path.c_str());

    // Открытие файла
    File file = SD.open(path, FILE_READ);
    if (!file) {
        Serial.println("[SD] File open error!");
        return;
    }

    // Чтение файла
    size_t size = file.size();
    uint8_t* buffer = (uint8_t*)ps_malloc(size);
    if (!buffer) {
        Serial.println("[SD] Buffer alloc failed!");
        file.close();
        return;
    }

    if (file.read(buffer, size) != size) {
        Serial.println("[SD] File read error!");
        free(buffer);
        file.close();
        return;
    }
    file.close();

    // Отрисовка
    if (!gfx.drawJpg(buffer, size, 0, 0, LCD_H_RES, LCD_V_RES)) {
        Serial.println("[SD] DrawJpg failed!");
    }
    free(buffer);

    delay(display_time);
}