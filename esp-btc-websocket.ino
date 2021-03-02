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

  Serial.print("[WiFi] Connecting to: ");
  Serial.print(WIFI_SSID);
  Serial.print("..");

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("[WiFi] Connected to network, IP: ");
  Serial.println(WiFi.localIP());

  Serial.println("[Display] Setup");
  display.setBrightness(0);

  Serial.println("[WebSocket] Setup");
  wsConnect();

  websocket.onMessage([&](WebsocketsMessage message) {
    Serial.print("[WebSocket] New message: ");
    Serial.println(message.data());

    DynamicJsonDocument doc(384);
    DeserializationError error = deserializeJson(doc, message.data());
    if (error) {
      Serial.print("[WebSocket] Could not deserialize JSON: ");
      Serial.println(error.f_str());
      return;
    }

    int price = doc["data"]["p"];
    Serial.print("[WebSocket] Serialized json! Bitcoin price: ");
    Serial.println(price);

    printNumberToDisplay(price);
  });
}

void loop() {
  if (websocket.available()) {
    websocket.poll();
    websocket.ping();
  } else {
    Serial.println("Websocket is not available!");
    wsConnect();
  }
}

void wsConnect() {
  if (websocket.connect("wss://fstream.binance.com/stream?streams=btcusdt@markPrice")) {
    Serial.println("[WebSocket] Connected!");
    websocket.ping();
    return;
  }

  Serial.println("[WebSocket] Not connected!");
  delay(1000);
  wsConnect();
}

int previousDigits = 1;
void printNumberToDisplay(int number) {
  int digits;
  if (number > 99999) {
    digits = 6;
  } else if (number > 9999) {
    digits = 5;
  } else if (number > 999) {
    digits = 4;
  } else if (number > 99) {
    digits = 3;
  } else if (number > 9) {
    digits = 2;
  } else {
    digits = 1;
  }

  if (previousDigits != digits) {
    previousDigits = digits;
    display.clear();
  }

  display.showNumberDec(number, false, digits);
}
