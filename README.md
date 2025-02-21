# Wii Remote Controlled Rover with ESP8266

This project demonstrates how to control a rover using a Nintendo Wii Remote, connected wirelessly to an ESP8266. The ESP8266 receives data from the Wii Remote and sends commands to the rover's motors, allowing the user to control the rover's movement remotely.

## Components Required

- **ESP8266** (NodeMCU or Wemos D1 mini)
- **Nintendo Wii Remote** (with Bluetooth support)
- **Rover chassis** (with motors and motor driver)
- **Motor Driver** (L298N or similar)
- **Power Supply** for the rover (battery pack)
- **Jumper wires** and **breadboard** (optional)
- **Bluetooth dongle** (if not using a built-in Bluetooth adapter)

## Features

- Control rover movement (forward, backward, left, right)
- Adjustable speed control
- Full integration with the Wii Remote buttons
- Wireless communication via ESP8266

## Setup Instructions

### Hardware Setup

1. **ESP8266**: Connect the ESP8266 to your motor driver and rover motors according to your motor driver specifications (e.g., L298N).
2. **Motor Driver**: Wire the motor driver to the motors of your rover. Use jumper wires to connect the motor driver to the GPIO pins of the ESP8266.
3. **Power Supply**: Power the ESP8266 and motor driver using an appropriate power supply. Typically, the ESP8266 can be powered with a 5V USB adapter, and the rover's motors need a separate battery (e.g., 7.4V LiPo battery).

### Software Setup

1. **Install Libraries**:
    - Install the necessary libraries in the Arduino IDE for the ESP8266, such as:
      - `ESP8266WiFi`
      - `Wiimote`
      - `Adafruit_Motor_Shield` (if using Adafruit motor shield)
      - Or any other motor control library specific to your motor driver.

2. **Pairing the Wii Remote**:
    - Pair the Wii Remote with the ESP8266 using Bluetooth. You might need a Bluetooth dongle connected to the ESP8266 for this step, or you can connect directly if the ESP8266 has a Bluetooth module (e.g., ESP32 with Bluetooth support).
    - Use a library such as `Wiimote` for communicating with the Wii Remote.

3. **Programming the ESP8266**:
    - Use the Arduino IDE to program the ESP8266. Upload the code to handle the communication between the Wii Remote and the motor controller.
