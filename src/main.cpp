#include "wifi_manager.h"
#include "device_registration.h"
#include "card_reader.h"
#include "ws_client.h"
#include "led_control.h"

void setup() {
    Serial.begin(115200);

    wifiConnect();
    ledInit();
    wsInit();

    Serial.println("Введите код регистрации:");
    while (!Serial.available()) {}
    String code = Serial.readStringUntil('\n');

    if (!registerDevice(code)) {
        Serial.println("Регистрация не удалась");
        while (true);
    }
}

void loop() {
    wsLoop();   // 👈 ВАЖНО

    String uid;
    if (readCard(uid)) {
        wsSendCard(uid);
        delay(500);

        if (wsHasAccess())
            ledAccessGranted();
        else
            ledAccessDenied();
    }
}
