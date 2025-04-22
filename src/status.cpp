#include "status.h"

void status_display_display_ok() {
    gfx.fillScreen(TFT_BLACK);
    gfx.setTextSize(3);
    gfx.setTextColor(TFT_GREEN);
    gfx.setCursor(100, 50);
    gfx.print("Display: OK");
}

void status_display_wifi(const String& ssid) {
    gfx.setTextColor(TFT_WHITE);
    gfx.setCursor(100, 100);
    gfx.print("WiFi: ");
    gfx.setTextColor(TFT_YELLOW);
    gfx.print(ssid);
}

void status_display_wifi_result(bool connected, const IPAddress& ip) {
    gfx.setTextSize(3);
    gfx.setCursor(100, 150);
    if (connected) {
        gfx.setTextColor(TFT_GREEN);
        gfx.print("Connected");
        gfx.setCursor(100, 200);
        gfx.print("IP: ");
        gfx.print(ip);
    } else {
        gfx.setTextColor(TFT_RED);
        gfx.print("Failed");
    }
}

void status_display_sd(bool success) {
    gfx.setTextColor(success ? TFT_GREEN : TFT_RED);
    gfx.setCursor(100, 250);
    gfx.print(success ? "SD: OK" : "SD ERROR");
}

void status_display_ready() {
    gfx.setTextColor(TFT_GREEN);
    gfx.setCursor(100, 300);
    gfx.print("Ready!");
}