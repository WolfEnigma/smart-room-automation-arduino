# Methodology

## System Design
The Automated Smart Room is designed using a modular approach. The system is divided into sensing, processing, and actuation units to ensure reliability and scalability.

## Microcontroller Selection
- **NodeMCU ESP8266**: Used as the central automation controller due to its built-in Wi-Fi capability.
- **Arduino Uno**: Used for the smart door lock system for enhanced reliability and ease of keypad integration.

## Sensor Integration
- Temperature and humidity monitoring using DHT11
- Light intensity detection using LDR
- Smoke detection using MQ-2 sensor
- Rain detection using raindrop sensor
- Proximity detection using ultrasonic sensor

## Automation Logic
Sensor data is continuously monitored. When predefined threshold conditions are met, the system automatically triggers corresponding actuators such as relays, motors, buzzers, or solenoid locks.

## IoT Integration
NodeMCU ESP8266 enables remote monitoring and control through Wi-Fi-based platforms such as the Blynk application.
