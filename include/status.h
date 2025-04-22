#pragma once

#include <Arduino.h>
#include "display.h" // Для доступа к gfx

// Отображение статуса дисплея ("Display: OK")
void status_display_display_ok();

// Отображение статуса Wi-Fi ("WiFi: SSID")
void status_display_wifi(const String& ssid);

// Отображение результата подключения Wi-Fi ("Connected"/"Failed", IP)
void status_display_wifi_result(bool connected, const IPAddress& ip);

// Отображение статуса SD-карты ("SD: OK" или "SD ERROR")
void status_display_sd(bool success);

// Отображение готовности ("Ready!")
void status_display_ready();