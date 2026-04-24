IoT Smart Monitoring System (ESP32, Wokwi Simulation)

Overview

This project demonstrates an ESP32-based IoT monitoring system simulated on Wokwi. It integrates multiple sensors and actuators to provide environmental monitoring and alert mechanisms.

Features

Ultrasonic Sensor (HC-SR04): Measures distance.

DHT22 Sensor: Monitors temperature and humidity.

LED (limegreen): Visual indicator.

Buzzer: Audible alerts.

Slide Switch: Manual control.

Circuit Diagram

The circuit includes ESP32 DevKit, ultrasonic sensor, DHT22, LED, buzzer, and switch. The wiring is defined in diagram.json. A screenshot of the circuit can be added under /docs/diagram.png.

Simulation

▶️ Run on Wokwi

Libraries Used

Blynk

DHT sensor library

DHT sensor library for ESPx

LiquidCrystal I2C

How to Run

Clone the repository.

Open in Arduino IDE or PlatformIO.

Install required libraries listed in libraries.txt.

Upload the code to ESP32.

Repository Structure

/project-root
  ├── src/                # Main code files
  ├── docs/               # Diagrams, documentation, screenshots
  ├── libraries.txt       # Dependencies list
  ├── diagram.json        # Wokwi circuit diagram
  ├── wokwi-project.txt   # Simulation link (optional)
  └── README.md           # Project overview

Future Improvements

Add cloud logging (Firebase/MQTT).

Expand sensor set (gas sensor, motion sensor).
