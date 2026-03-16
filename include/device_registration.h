#ifndef DEVICE_REGISTRATION_H
#define DEVICE_REGISTRATION_H

#include <Arduino.h>

// Основная функция регистрации устройства
bool registerDevice(const String& regCode);

// Функции для работы с сохраненным токеном
String getStoredToken();
bool hasStoredToken();
void clearStoredToken();

#endif