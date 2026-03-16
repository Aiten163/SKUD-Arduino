#include "ws_client.h"
#include "config.h"
#include <WebSocketsClient.h>

static WebSocketsClient ws;
static bool accessGranted = false;
static String deviceToken = "";

void wsSetToken(String token) {
    deviceToken = token;
}

static void wsEvent(WStype_t type, uint8_t * payload, size_t length) {
    switch(type) {
        case WStype_DISCONNECTED:
            Serial.println("[WSc] Disconnected!");
            accessGranted = false;
            break;
            
        case WStype_CONNECTED:
            Serial.println("[WSc] Connected to server!");
            
            // Отправляем токен при подключении
            if (deviceToken.length() > 0) {
                String authMsg = "{\"type\":\"auth\",\"token\":\"" + deviceToken + "\"}";
                ws.sendTXT(authMsg);
                
                Serial.println("[WSc] Token sent for authentication");
            }
            break;
            
        case WStype_TEXT:
            {
                String msg = (char*)payload;
                Serial.println("[WSc] Received: " + msg);
                
                if (msg == "ACCESS_OK" || msg.indexOf("ACCESS_OK") >= 0) {
                    accessGranted = true;
                } else if (msg == "ACCESS_DENIED" || msg.indexOf("ACCESS_DENIED") >= 0) {
                    accessGranted = false;
                } else if (msg == "AUTH_OK" || msg.indexOf("AUTH_OK") >= 0) {
                    Serial.println("[WSc] Authentication successful!");
                } else if (msg == "AUTH_FAILED" || msg.indexOf("AUTH_FAILED") >= 0) {
                    Serial.println("[WSc] Authentication failed!");
                }
            }
            break;
            
        case WStype_BIN:
            Serial.println("[WSc] Binary data received (length: " + String(length) + ")");
            break;
            
        case WStype_ERROR:
            Serial.println("[WSc] Error occurred!");
            break;
            
        case WStype_PING:
            Serial.println("[WSc] Ping received");
            break;
            
        case WStype_PONG:
            Serial.println("[WSc] Pong received");
            break;
    }
}

void wsInit() {
    ws.begin(SERVER_HOST, SERVER_PORT, WS_PATH);
    ws.onEvent(wsEvent);
    ws.setReconnectInterval(5000); // Пытаемся переподключаться каждые 5 секунд
    
    // Настройки для стабильной работы
    ws.enableHeartbeat(15000, 3000, 2); // Heartbeat для поддержания соединения
}

void wsLoop() {
    ws.loop();
}

void wsSendCard(String uid) {
    if (deviceToken.length() == 0) {
        Serial.println("[WSc] Cannot send card: no token!");
        return;
    }
    
    String cardMsg = "{\"type\":\"card\",\"uid\":\"" + uid + "\",\"token\":\"" + deviceToken + "\"}";
    ws.sendTXT(cardMsg);
}

bool wsHasAccess() {
    return accessGranted;
}