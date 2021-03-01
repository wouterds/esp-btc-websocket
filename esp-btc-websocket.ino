#include <Arduino.h>
#include <WiFi.h>
// #include <SevenSegmentTM1637.h>
#include <TM1637Display.h>
#include "env.h"

// SevenSegmentTM1637 display(PIN_CLK, PIN_DIO);
TM1637Display display(PIN_CLK, PIN_DIO);

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
  // display.begin(6);
  // display.setBacklight(20);
  // display.clear();
  display.setBrightness(0x0f);
  display.clear();
}

void loop() {
  // display.print('654321');
  // delay(2000);
  // display.clear();
  //
  // display.print('000000');
  display.clear();
  display.showNumberDec(1, false, 1, 0);
  delay(1000);

  display.clear();
  display.showNumberDec(1, false, 1, 1);
  delay(1000);

  display.clear();
  display.showNumberDec(1, false, 1, 2);
  delay(1000);

  display.clear();
  display.showNumberDec(1, false, 1, 3);
  delay(1000);

  display.clear();
  display.showNumberDec(1, false, 1, 4);
  delay(1000);

  display.clear();
  display.showNumberDec(1, false, 1, 5);
  delay(1000);
  // display.clear();
}
