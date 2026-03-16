#include <Arduino.h>
#include "config.h"
#include "led_control.h"

#define LED_PIN 16

void ledInit() {
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);
}

void ledOn() {
    digitalWrite(LED_PIN, HIGH);
}

void ledOff() {
    digitalWrite(LED_PIN, LOW);
}

void ledBlink(int times) {
    for (int i = 0; i < times; i++) {
        digitalWrite(LED_PIN, HIGH);
        delay(300);
        digitalWrite(LED_PIN, LOW);
        delay(300);
    }
}

void ledAccessGranted() {
    ledOn();
}

void ledAccessDenied() {
    ledBlink(3);
}
