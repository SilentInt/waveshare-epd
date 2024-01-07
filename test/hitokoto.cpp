#include "hitokoto.h"

void wifi_connect()
{
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
}

// 请求一言api
// https://v1.hitokoto.cn/?c=a&encode=text
// 使用httpclient
String get_hitokoto()
{
  HTTPClient http;
  http.begin("https://v1.hitokoto.cn/?c=a&encode=text");
  int httpCode = http.GET();
  String payload;
  if (httpCode == 200)
  {
    payload = http.getString();
  }
  else
  {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }
  http.end();
  return payload;
}