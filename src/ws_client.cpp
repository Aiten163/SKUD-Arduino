#include "ws_client.h"
#include "config.h"
#include <WebSocketsClient.h>

static WebSocketsClient ws;
static bool accessGranted = false;

static void wsEvent(WStype_t type, uint8_t * payload, size_t length) {
    if (type == WStype_TEXT) {
        String msg = (char*)payload;
        accessGranted = (msg == "ACCESS_OK");
    }
}

void wsInit() {
    ws.begin(SERVER_HOST, SERVER_PORT, WS_PATH);
    ws.onEvent(wsEvent);
}

void wsLoop() {
    ws.loop();
}

void wsSendCard(String uid) {
    ws.sendTXT(uid);
}


bool wsHasAccess() {
    return accessGranted;
}
