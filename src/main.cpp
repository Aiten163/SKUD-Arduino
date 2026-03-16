#include <Arduino.h>
#include "config.h"
#include "wifi_manager.h"
#include "device_registration.h"
#include "card_reader.h"
#include "ws_client.h"
#include "led_control.h"

void setup() {
    Serial.begin(115200);
    delay(1000); // Небольшая задержка для стабильности
    
    Serial.println("\n\n=== Device Starting ===");
    
    wifiConnect();
    ledInit();
    String TOKEN = "";
    
    // Получаем токен до инициализации WebSocket
    if(hasStoredToken() == true) {
        TOKEN = getStoredToken();
        Serial.println("Token loaded from storage");
    } else {
        Serial.println("No token found, starting registration...");
        
        bool registrationSuccess = false;
        while (!registrationSuccess) {
            Serial.println("Enter registration code:");
            
            while (!Serial.available()) {
                delay(100);
            }
            
            String code = Serial.readStringUntil('\n');
            code.trim();
            
            if (code.length() > 0) {
                if (registerDevice(code)) {
                    registrationSuccess = true;
                    TOKEN = getStoredToken();
                    Serial.println("Registration successful!");
                    Serial.println("Token: " + TOKEN);
                } else {
                    Serial.println("Invalid registration code. Try again.");
                    Serial.println();
                }
            } else {
                Serial.println("Code cannot be empty. Try again.");
                Serial.println();
            }
        }
    }
    
    // Устанавливаем токен для WebSocket клиента
    wsSetToken(TOKEN);
    
    // Инициализируем WebSocket соединение
    wsInit();
    
    Serial.println("Setup complete. Waiting for cards...");
}

void loop() {
    wsLoop(); // Поддерживаем WebSocket соединение
    
    String uid;
    if (readCard(uid)) {
        Serial.println("Card detected: " + uid);
        
        wsSendCard(uid);
        delay(500); // Даем время на получение ответа
        
        // Проверяем несколько раз с небольшими задержками
        for(int i = 0; i < 10; i++) {
            wsLoop();
            if (wsHasAccess()) {
                ledAccessGranted();
                Serial.println("Access GRANTED");
                break;
            }
            delay(50);
        }
        
        if (!wsHasAccess()) {
            ledAccessDenied();
            Serial.println("Access DENIED");
        }
        
        // Сбрасываем флаг доступа для следующей карты
        // accessGranted будет сброшен при следующем ответе от сервера
    }
    
    delay(10); // Небольшая задержка для стабильности
}