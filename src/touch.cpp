#include "touch.h"
#include <Wire.h>
#include <TCA9534.h>

extern TCA9534 ioex; // Используем ioex из display.cpp
static TAMC_GT911 tp = TAMC_GT911(15, 16, 38, 1, 800, 480); // SDA: 15, SCL: 16, INT: 38, RST: 1

void touch_init() {
    Serial.println("[Touch] Initializing GT911");
    Wire.setClock(400000); // Ускоряем I2C до 400 кГц

    // Настройка TCA9534
    ioex.config(1, TCA9534::Config::OUT);
    ioex.config(2, TCA9534::Config::OUT);
    ioex.output(1, TCA9534::Level::H); // Подсветка
    ioex.output(2, TCA9534::Level::L); // Сброс GT911
    delay(20);
    ioex.output(2, TCA9534::Level::H);
    delay(100);

    // Настройка пина RST
    pinMode(1, OUTPUT);
    digitalWrite(1, LOW);
    delay(20);
    digitalWrite(1, HIGH);
    delay(100);
    pinMode(1, INPUT);

    // Настройка пина INT
    pinMode(38, INPUT_PULLUP);

    tp.begin();
    tp.reset(); // Дополнительный сброс GT911
    Serial.println("[Touch] GT911 initialized");
}

void touchpad_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data) {
    tp.read();
    if (tp.isTouched) {
        data->state = LV_INDEV_STATE_PR;
        data->point.x = tp.points[0].x;
        data->point.y = tp.points[0].y;
        Serial.printf("[Touch] Pressed: x=%d, y=%d\n", data->point.x, data->point.y);
    } else {
        data->state = LV_INDEV_STATE_REL;
        Serial.println("[Touch] Released");
    }
}