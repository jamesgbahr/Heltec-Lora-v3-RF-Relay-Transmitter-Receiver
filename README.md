# Heltec LoRa v3 RF Relay Transmitter & Receiver

This repository contains the codebase for a **3-Channel Momentary Switch Relay System** built using Heltec LoRa v3 modules. The system consists of a **transmitter** and a **receiver**, communicating over the LoRa network for wireless relay control.

## Features:
- **Three independent channels**: Control up to three momentary relays remotely.
- **LoRa Communication**: Robust long-range communication using LoRa technology.
- **Momentary Switching**: Each channel is designed for momentary switching, ideal for applications requiring short-duration activations.
- **Configurable Parameters**: Easily adjust LoRa frequency, power, and other communication settings.
- **Efficient Power Management**: Optimized for low power consumption to support battery-powered deployments.

## Applications:
- **Pyrotechnic Firing Triggers**: Safe and reliable wireless ignition of fireworks, special effects, and other pyrotechnic systems.
- Home automation
- Remote equipment control
- Industrial automation
- IoT projects

## Components:
- **Heltec LoRa v3 Modules**: Acts as the transmitter and receiver.
- **Relay Modules**: Supports up to three channels for triggering external devices.
- **LoRa Protocol**: Ensures reliable communication over long distances.

## Getting Started:
1. **Upload the transmitter code** to the transmitting Heltec module.
2. **Upload the receiver code** to the receiving Heltec module.
3. **Connect the relay modules** to the receiver, following the pinout specified in the code.
4. **Power up both modules**, and you're ready to control relays wirelessly.

## Requirements:
- **Heltec LoRa v3 Modules**
- **Arduino IDE**
- **Compatible relay modules**
- **[Heltec Unofficial Library](https://github.com/HelTecAutomation/Heltec_ESP32)** (must be installed in the Arduino IDE)
- **Required libraries** (specified in the code comments)

## About:
This codebase was written for **[PyrotechnicFX.com](https://www.pyrotechnicfx.com)** trigger systems to provide a safe and reliable solution for wireless pyrotechnic control and automation.

## Contributions:
Feel free to fork this repository and contribute improvements or bug fixes! Collaboration is encouraged to enhance functionality and reliability.

---

Keep the system safe and secure, and enjoy building wireless relay solutions with LoRa! 🚀
