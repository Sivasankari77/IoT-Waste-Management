# Smart Campus Waste Management System

An IoT-based waste bin monitoring system using ESP32 and Blynk.

## Features
- Ultrasonic sensor to detect bin fill level
- DHT22 for temperature & humidity monitoring
- LCD display showing live readings
- Buzzer + LED alert when bin is full
- Remote monitoring via Blynk app

## Hardware Used
- ESP32 DevKit C V4
- HC-SR04 Ultrasonic Sensor
- DHT22 Temperature & Humidity Sensor
- LCD 16x2 (I2C)
- Buzzer
- LEDs

## Simulate on Wokwi
https://wokwi.com/projects/399048781614584833

## Libraries Required
- Blynk
- DHT sensor library
- LiquidCrystal I2C

## Setup
1. Install libraries listed in `libraries.txt`
2. Replace `YOUR_BLYNK_AUTH_TOKEN_HERE` in `sketch.ino` with your actual token
3. Update WiFi credentials in `sketch.ino`
4. Upload to ESP32
