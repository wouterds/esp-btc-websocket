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
  showNumberDec(3);
  delay(1000);
  showNumberDec(2);
  delay(1000);
  showNumberDec(1);
  delay(1000);

  Serial.println("Starting counter!");
  for (int i = 1; i <= 999999; i++) {
    Serial.print("count: ");
    Serial.println(i);
    showNumberDec(i);
    delay(10);
  }

  delay(3000);
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
