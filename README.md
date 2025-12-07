# New-BLE-Library-for-ESP32-Mouse-and-Keyboard-and-Combo 🖱️⌨️

[![C/C++](https://img.shields.io/badge/language-C%2B%2B%2FC-blue?style=for-the-badge&logo=cpp)](https://github.com/LegedsDaD/New-BLE-Library-for-ESP32-Mouse-and-Keyboard-and-Combo)
[![License](https://img.shields.io/badge/license-MIT-green?style=for-the-badge)](#license)
[![Build Status](https://img.shields.io/badge/build-passing-brightgreen?style=for-the-badge)](#)  
[![Platform](https://img.shields.io/badge/platform-ESP32-blue?style=for-the-badge&logo=Espressif)](https://www.espressif.com)

> **Version:** 0.06 —
>  Next Version 1.0 coming soon.  

## About

This is a BLE (Bluetooth Low Energy) library for ESP32 that enables emulating a **mouse**, **keyboard**, or **combo HID device** — useful for projects requiring wireless HID input via ESP32.

## Features

- BLE-based HID support: mouse, keyboard, and combo (mouse + keyboard)  
- Easy-to-use API for sending mouse movements, clicks, keyboard keypresses  
- Compact C++ implementation compatible with ESP32 toolchains  
- Configurable HID descriptors via `HIDDescriptors.h`

## Getting Started

### Requirements

- ESP32 development board  
- Arduino-ESP32 core (or other ESP32-compatible build environment)  
- BLE support enabled

### Installation

1. Clone the repo  
   ```bash
   git clone https://github.com/LegedsDaD/New-BLE-Library-for-ESP32-Mouse-and-Keyboard-and-Combo.git
