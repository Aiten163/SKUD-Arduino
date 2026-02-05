#include "card_reader.h"
#include "config.h"
#include <MFRC522.h>

MFRC522 rfid(RFID_SS_PIN, RFID_RST_PIN);


bool readCard(String &uid) {
    if (!rfid.PICC_IsNewCardPresent()) return false;
    if (!rfid.PICC_ReadCardSerial()) return false;

    uid = "";
    for (byte i = 0; i < rfid.uid.size; i++) {
        uid += String(rfid.uid.uidByte[i], HEX);
    }
    rfid.PICC_HaltA();
    return true;
}
