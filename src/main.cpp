#include "display.h"
#include "sd_card.h"
#include "wifi.h"
#include "ui.h"
#include "touch.h"
#include <WiFiMulti.h>
#include <lvgl.h>

WiFiMulti wifiMulti;
String ssid = "NETGEAR_11N";
String password = "pass";

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[800 * 480 / 10];

void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) {
    gfx.startWrite();
    gfx.setAddrWindow(area->x1, area->y1, area->x2 - area->x1 + 1, area->y2 - area->y1 + 1);
    gfx.pushPixels((uint16_t*)&color_p->full, (area->x2 - area->x1 + 1) * (area->y2 - area->y1 + 1), true);
    gfx.endWrite();
    lv_disp_flush_ready(disp);
}

void setup() {
    Serial.begin(115200);
    while (!Serial) delay(10);
    Serial.println("[Main] Starting setup");

    display_init();
    Serial.println("[Main] Display initialized");

    lv_init();
    lv_disp_draw_buf_init(&draw_buf, buf, NULL, 800 * 480 / 10);
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = 800;
    disp_drv.ver_res = 480;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);
    Serial.println("[Main] LVGL initialized");

    gfx.fillScreen(TFT_BLACK); // Очистка экрана перед UI
    touch_init();
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = touchpad_read;
    lv_indev_drv_register(&indev_drv);
    Serial.println("[Main] Touch initialized");

    ui_init();
    Serial.println("[Main] UI initialized");

    wifi_init(wifiMulti, ssid, password);
    Serial.println("[Main] WiFi initialized");

    randomSeed(millis()); // Исправлено для избежания ошибки ADC
    bool sd_success = sd_init();
    if (!sd_success) {
        Serial.println("[Main] SD card failed, halting");
        while (1) delay(1000);
    }
    Serial.println("[Main] SD card initialized");
}

void loop() {
    lv_timer_handler();
    delay(5);
    wifi_check(wifiMulti);
    if (Serial.available()) {
        char c = Serial.read();
        if (c == 's') {
            Serial.println("[Main] Starting JPG display via Serial");
            sd_display_random_jpg(30000);
        }
    }
    if (get_current_mode() == 0) {
        // Демонстрация начнётся только после нажатия кнопки
    } else if (get_current_mode() == 1) {
        Serial.println("[Main] Online mode: Grok placeholder");
        delay(1000);
    }
}