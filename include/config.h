#pragma once

/************ Wi-Fi ************/
#define WIFI_SSID     "Tot"
#define WIFI_PASSWORD "8888VVVV"

/************ Server ************/
#define SERVER_HOST   "192.168.0.173"
#define SERVER_PORT   8080

#define HTTP_REGISTER_URL "http://192.168.0.173/register"
#define WS_PATH          "/ws"

/************ Hardware ************/
#define LED_GREEN_PIN 26
#define LED_RED_PIN   27

#define RFID_SS_PIN   5
#define RFID_RST_PIN  22


#ifndef CONFIG_H
#define CONFIG_H

/***** LED *****/
#define LED_PIN 2
#define LED_BLINK_DELAY 200

#endif