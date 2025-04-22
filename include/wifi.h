#pragma once

#include <Arduino.h>
#include <WiFiMulti.h>
#include "display.h" // Для доступа к gfx

// Инициализация Wi-Fi
void wifi_init(WiFiMulti& wifiMulti, const String& ssid, const String& password);

// Проверка и автопереподключение Wi-Fi
void wifi_check(WiFiMulti& wifiMulti);