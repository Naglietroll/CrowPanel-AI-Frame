#include "display.h"
#include "pins_config.h"

TCA9534 ioex;
LGFX gfx;

void display_init() {
    Serial.begin(115200);

    // Инициализация I2C и TCA9534 для подсветки
    Wire.begin(15, 16);
    delay(50);
    ioex.attach(Wire);
    ioex.setDeviceAddress(0x18);
    ioex.config(1, TCA9534::Config::OUT);
    ioex.config(2, TCA9534::Config::OUT);

    // Включение подсветки
    ioex.output(1, TCA9534::Level::H);
    delay(20);
    ioex.output(2, TCA9534::Level::H);
    delay(100);

    // Инициализация дисплея
    gfx.init();
    gfx.initDMA();
    gfx.startWrite();
    // Убрали gfx.fillScreen(TFT_WHITE), чтобы не ломать LVGL
}