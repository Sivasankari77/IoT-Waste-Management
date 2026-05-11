#define BLYNK_PRINT Serial
#define BLYNK_AUTH_TOKEN "YOUR_BLYNK_AUTH_TOKEN_HERE" // Get your token from blynk.cloud → Template → Auth Token
#define BLYNK_TEMPLATE_ID "TMPL34caXjjnR"
#define BLYNK_TEMPLATE_NAME "Smart Campus Waste Management  System"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Your WiFi credentials.
char ssid[] = "Wokwi-GUEST";
char pass[] = "";

#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "DHTesp.h"
#include <DHT.h>

// Pins
#define TRIG_PIN 4
#define ECHO_PIN 0
#define DHT_PIN 15
#define DHT_TYPE DHT22

#define LED_PIN1 2
#define LED_PIN2 17
#define SPEAKER_PIN 16

#define SDA 13                    //Define SDA pins
#define SCL 14                    //Define SCL pins

LiquidCrystal_I2C lcd(0x27, 16, 2); 
DHT dht(DHT_PIN, DHT_TYPE);

BlynkTimer timer;

bool ledState = false; // Variable to store the state of the LED

void sendSensorData() {
  // Ultrasonic sensor
  long duration, distance;
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration / 2) / 29.1; // Convert to cm

  // DHT sensor
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Send data to Blynk
  Blynk.virtualWrite(V1, distance);
  Blynk.virtualWrite(V2, temperature);
  Blynk.virtualWrite(V3, humidity);

  // Check if bin is full
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
    digitalWrite(LED_PIN2, LOW);
    lcd.clear();
    lcd.print("Bin has Space");
  }
}

// Blynk widget configuration
// V1: Distance Widget (Value Display)
// V2: Temperature Widget (Value Display)
// V3: Humidity Widget (Value Display)
// V4: Notification Widget (Terminal)
// V5: Start/Stop Button (Button)
// V6: LED Control Button (Button)

BLYNK_WRITE(V5) {
  int startStop = param.asInt();
  if (startStop == 1) {
    sendSensorData(); // Start sending sensor data
  } else {
    // Stop sending sensor data
    // You can add additional actions if needed
  }
}

BLYNK_WRITE(V6) {
  ledState = param.asInt(); // Read the state of the Button widget
  digitalWrite(LED_PIN1, ledState); // Set the LED pin based on the button state (ON/OFF)
}

void setup() {
  Wire.begin(SDA, SCL);           
  if (!i2CAddrTest(0x27)) {   
    lcd = LiquidCrystal_I2C(0x3F, 16, 2);  
  }
  lcd.init();             
  lcd.backlight(); 

  lcd.setCursor(0, 0); 
  lcd.print("Smart Campus");
  lcd.setCursor(0, 1);
  lcd.print("Waste Management");
  delay(2500);
  lcd.clear();
  lcd.print(" Version 0.0.1");

  pinMode(5, INPUT_PULLUP);
  pinMode(LED_PIN1, OUTPUT);
  pinMode(LED_PIN2, OUTPUT);
  pinMode(SPEAKER_PIN, OUTPUT);
  Serial.begin(115200);
  Serial.println("Serial Prints Starts...");

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  dht.begin();

  // Set a timer to send sensor data every 10 seconds
  timer.setInterval(10000L, sendSensorData);
}

void loop() {
  Blynk.run();
  timer.run();

  // DHT sensor
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: " + String(temperature, 2) + " C");
  lcd.setCursor(0, 1);
  lcd.print("Humidity: " + String(humidity, 1) + "%");

  delay(5000);
}

bool i2CAddrTest(uint8_t addr) {
  Wire.begin();
  Wire.beginTransmission(addr);
  if (Wire.endTransmission() == 0) {
    return true;
  }
  return false;
}
