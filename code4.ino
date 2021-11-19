#include <ESP8266WiFi.h>
#include <Wire.h>
#include <SPI.h>
#include “ClosedCube_MAX30205.h”

ClosedCube_MAX30205 max30205;

#define LED1 12

//wifi
const char* ssid     = 接続するwi-fiのSSID
const char* password = wi-fiのパスワード
const char* host = 接続するサーバのドメイン

#define LED2 13
#define BME_VIN 14

void setup() {
  Serial.begin(115200);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  pinMode(BME_VIN, OUTPUT);

  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(BME_VIN, LOW);

  max30205.begin(0x48);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(“.”);
  }
}

void loop() {
  digitalWrite(BME_VIN, HIGH);

  max30205.begin(0x48);

  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, LOW);
  delay(100);

  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);

  Serial.print(“T=”);

  float tempValue = max30205.readTemperature();
  digitalWrite(BME_VIN, LOW);

  Serial.print(tempValue);
  Serial.println(“C”);
  delay(300);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println(“connection failed”);
    return;
  }

  //気温をfloatからStringに変換
  String tempString = String(tempValue);

  String url = “/サーバのPHPへのパス/upload.php?temp=” + tempString;
  Serial.print(“Requesting URL: “);
  Serial.println(url);

  client.println(String(“GET “) + url + “ HTTP/1.1\r\n” +
                 “Host: “ + host + “\r\n” );
  delay(1000);

  while (client.available()) {
    String line = client.readStringUntil(‘\r’);
    Serial.print(“line:”);
    Serial.print(line);
  }

  ESP.deepSleep(1 * 60 * 1000 * 1000, WAKE_RF_DEFAULT);
  delay(1000);
}