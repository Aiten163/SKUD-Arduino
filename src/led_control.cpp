#include "led_control.h"
#include "config.h"
#include <Arduino.h>

void ledInit() {
    pinMode(LED_GREEN_PIN, OUTPUT);
    pinMode(LED_RED_PIN, OUTPUT);
}

void ledAccessGranted() {
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_RED, LOW);
}

void ledAccessDenied() {
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_RED, HIGH);
}
