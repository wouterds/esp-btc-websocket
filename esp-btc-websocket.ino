#include <Arduino.h>
#include <WiFi.h>
#include <TM1637Display.h>
#include "env.h"

TM1637Display display(PIN_CLK, PIN_DIO, DEFAULT_BIT_DELAY, 6);

void setup() {
  Serial.begin(115200);
  Serial.println();

  Serial.print("[WiFi] Connecting to: ");
  Serial.print(WIFI_SSID);
  Serial.print("..");

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("[WiFi] Connected to network, IP: ");
  Serial.println(WiFi.localIP());

  Serial.println("[Display] Setup");
  display.setBrightness(0x0f);
  display.clear();
}

void loop() {
  uint32_t number = 123456;

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
  display.showNumberDec(number, false, digits, 3);
  delay(100);
}
