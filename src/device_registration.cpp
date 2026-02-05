#include "device_registration.h"
#include "config.h"
#include <HTTPClient.h>
#include <WiFi.h>

bool registerDevice(const String& regCode) {
    if (WiFi.status() != WL_CONNECTED) {
        return false;
    }

    HTTPClient http;
    http.begin(HTTP_REGISTER_URL);
    http.addHeader("Content-Type", "application/json");

    String payload = "{\"code\":\"" + regCode + "\"}";
    int httpCode = http.POST(payload);

    http.end();
    return httpCode == 200;
}
