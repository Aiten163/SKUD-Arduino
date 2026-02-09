#include <Arduino.h>
#include "config.h"
#include "led_control.h"

static void ledBlink(uint8_t times) {
    for (uint8_t i = 0; i < times; i++) {
        digitalWrite(LED_PIN, HIGH);
        delay(LED_BLINK_DELAY);
        digitalWrite(LED_PIN, LOW);
        delay(LED_BLINK_DELAY);
    }
}

void ledInit() {
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);
}

void ledAccessGranted() {
    ledBlink(1);
}

void ledAccessDenied() {
    ledBlink(2);
}
