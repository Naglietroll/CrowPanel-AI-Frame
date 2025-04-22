#include "wifi.h"
#include "status.h"

void wifi_init(WiFiMulti& wifiMulti, const String& ssid, const String& password) {
    // Настройка WiFi
    WiFi.mode(WIFI_STA);
    WiFi.setAutoReconnect(true);
    wifiMulti.addAP(ssid.c_str(), password.c_str());

    // Временно отключаем вывод статуса
    // status_display_wifi(ssid);

    // Подключение
    bool connected = false;
    unsigned long startTime = millis();
    while (millis() - startTime < 20000) {
        if (wifiMulti.run() == WL_CONNECTED) {
            connected = true;
            break;
        }
        delay(500);
    }

    // Временно отключаем вывод результата
    // status_display_wifi_result(connected, WiFi.localIP());
}

void wifi_check(WiFiMulti& wifiMulti) {
    if (WiFi.status() != WL_CONNECTED) {
        wifiMulti.run();
    }
}