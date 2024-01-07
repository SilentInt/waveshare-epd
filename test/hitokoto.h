#ifndef __HITOKOTO__
#define __HITOKOTO__
#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

const char ssid[] = "ikun_family";
const char password[] = "21056789";

void wifi_connect();
String get_hitokoto();

#endif