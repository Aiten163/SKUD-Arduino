#include "wifi_manager.h"
#include "config.h"
#include <WiFi.h>

void wifiConnect() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    Serial.print("Подключение к Wi-Fi");

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("\nWi-Fi подключён");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
}

bool wifiIsConnected() {
    return WiFi.status() == WL_CONNECTED;
}
