#include <Arduino.h>
#include <WiFi.h>
#include "env.h"

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
}

void loop() {
  delay(1000);
}
