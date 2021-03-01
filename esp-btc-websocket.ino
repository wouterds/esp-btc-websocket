#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <TM1637Display.h>
#include <ArduinoWebsockets.h>
#include <ArduinoJson.h>
#include "env.h"

using namespace websockets;

TM1637Display display(PIN_CLK, PIN_DIO, DEFAULT_BIT_DELAY, 6);
WebsocketsClient websocket;

void setup() {
  Serial.begin(115200);
  Serial.println();

  Serial.print(F("[WiFi] Connecting to: "));
  Serial.print(WIFI_SSID);
  Serial.print(F(".."));

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }
  Serial.println();

  Serial.print(F("[WiFi] Connected to network, IP: "));
  Serial.println(WiFi.localIP());

  Serial.println(F("[Display] Setup"));
  display.setBrightness(0x0f);
  display.clear();

  Serial.println(F("[WebSocket] Setup"));

  bool connected = websocket.connect(F("wss://fstream.binance.com/stream?streams=btcusdt@markPrice"));
  if (connected) {
      Serial.println(F("[WebSocket] Connected!"));
      websocket.ping();
  } else {
      Serial.println(F("[WebSocket] Not connected!"));
  }

  websocket.onMessage([&](WebsocketsMessage message){
      Serial.println(F("Got Message!"));
      Serial.println(message.data());

      StaticJsonDocument<512> doc;
      DeserializationError error = deserializeJson(doc, message.data());
      if (error) {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return;
      }

      int price = doc["data"]["p"];
      Serial.print(F("Serialized json! Price:"));
      Serial.println(price);
      showNumberDec(price);
  });
}

void loop() {
  if (websocket.available()) {
    websocket.poll();
  }
  delay(100);
}

uint8_t previousDigits = 1;
void showNumberDec(long number)
{
  uint8_t digits = 1;
  if (number > 9) {
    digits = 2;
  }
  if (number > 99) {
    digits = 3;
  }
  if (number > 999) {
    digits = 4;
  }
  if (number > 9999) {
    digits = 5;
  }
  if (number > 99999) {
    digits = 6;
  }

  if (previousDigits != digits) {
    display.clear();
  }
  previousDigits = digits;

  display.showNumberDec(number, false, digits);
}
