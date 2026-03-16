#include "device_registration.h"
#include "config.h"
#include <HTTPClient.h>
#include <WiFi.h>
#include <Preferences.h>

const char* PREF_NAMESPACE = "device";

bool registerDevice(const String& regCode) {
    if (WiFi.status() != WL_CONNECTED) {
        return false;
    }

    HTTPClient http;
    http.begin(HTTP_REGISTER_URL);
    http.addHeader("Content-Type", "application/json");

    String payload = "{\"code\":\"" + regCode + "\"}";
    int httpCode = http.POST(payload);

    bool success = false;
    
    if (httpCode == 200) {
        String response = http.getString();
        
        int successPos = response.indexOf("\"success\"");
        int tokenPos = response.indexOf("\"token\"");
        
        if (successPos != -1 && tokenPos != -1) {
            int successStart = response.indexOf(":", successPos) + 1;
            int successEnd = response.indexOf(",", successStart);
            String successStr = response.substring(successStart, successEnd);
            successStr.trim();
            success = (successStr == "true");
            
            if (success) {
                int tokenStart = response.indexOf(":", tokenPos) + 2;
                int tokenEnd = response.indexOf("\"", tokenStart);
                String token = response.substring(tokenStart, tokenEnd);
                
                Preferences preferences;
                preferences.begin(PREF_NAMESPACE, false);
                preferences.putString("token", token);
                preferences.end();
            }
        }
    }
    
    http.end();
    return success;
}

// Функция для получения сохраненного токена
String getStoredToken() {
    Preferences preferences;
    preferences.begin(PREF_NAMESPACE, true);
    String token = preferences.getString("token", "");
    preferences.end();
    return token;
}

// Функция для проверки наличия токена
bool hasStoredToken() {
    Preferences preferences;
    preferences.begin(PREF_NAMESPACE, true);
    bool hasToken = preferences.isKey("token");
    preferences.end();
    return hasToken;
}

// Функция для удаления сохраненного токена (при сбросе устройства)
void clearStoredToken() {
    Preferences preferences;
    preferences.begin(PREF_NAMESPACE, false);
    preferences.remove("token");
    preferences.end();
}