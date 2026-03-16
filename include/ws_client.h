#ifndef WS_CLIENT_H
#define WS_CLIENT_H

#include <Arduino.h>

void wsInit();
void wsLoop();
void wsSendCard(String uid);
bool wsHasAccess();
void wsSetToken(String token); // Новая функция

#endif