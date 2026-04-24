#define BLYNK_PRINT Serial
#define BLYNK_AUTH_TOKEN "YOUR_BLYNK_TOKEN"
#define BLYNK_TEMPLATE_ID "TMPL34caXjjnR"
#define BLYNK_TEMPLATE_NAME "Smart Campus Waste Management System"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <DHT.h>

// WiFi credentials
char ssid[] = "Wokwi-GUEST";
char pass[] = "";

// Pins
#define TRIG_PIN 4
#define ECHO_PIN 0
#define DHT_PIN 15
#define DHT_TYPE DHT22
#define LED_PIN1 2
#define LED_PIN2 17
#define SPEAKER_PIN 16
#define SDA 13
#define SCL 14

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHT_PIN, DHT_TYPE);
BlynkTimer timer;
bool ledState = false;

void sendSensorData() {
  // Ultrasonic
  long duration, distance;
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration / 2) / 29.1;

  // DHT
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Send to Blynk
  Blynk.virtualWrite(V1, distance);
  Blynk.virtualWrite(V2, temperature);
  Blynk.virtualWrite(V3, humidity);

  // Alerts
  if (distance < 10) {
    Blynk.virtualWrite(V4, "Waste bin is full!");
    tone(SPEAKER_PIN, 262, 250);
    digitalWrite(LED_PIN2, HIGH);
    digitalWrite(LED_PIN1, LOW);
    lcd.clear();
    lcd.print("Bin is Full!");
  } else {
    Blynk.virtualWrite(V4, "Bin has Space.");
    digitalWrite(LED_PIN1, HIGH);
    digitalWrite
