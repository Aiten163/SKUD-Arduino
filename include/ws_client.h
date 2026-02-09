#pragma once
#include <Arduino.h>

void wsInit();
void wsLoop();
void wsSendCard(String uid);
bool wsHasAccess();
