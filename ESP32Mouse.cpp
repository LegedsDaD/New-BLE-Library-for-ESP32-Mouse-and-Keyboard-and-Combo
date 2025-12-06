#include "ESP32Mouse.h"

void ESP32Mouse::begin(std::string name) {
    ESP32HID::begin(name);
    _buttons = 0;
}

void ESP32Mouse::sendReport(int8_t x, int8_t y, int8_t wheel) {
    uint8_t m[4];
    m[0] = _buttons;
    m[1] = x;
    m[2] = y;
    m[3] = wheel;

    // Send to MOUSE_ID (2)
    this->_hidDevice->inputReport(MOUSE_ID)->setValue(m, 4);
    this->_hidDevice->inputReport(MOUSE_ID)->notify();
}

void ESP32Mouse::move(int8_t x, int8_t y, int8_t wheel) {
    sendReport(x, y, wheel);
}

void ESP32Mouse::click(uint8_t b) {
    _buttons = b;
    move(0, 0, 0);
    _buttons = 0;
    move(0, 0, 0);
}

void ESP32Mouse::press(uint8_t b) {
    _buttons |= b;
    move(0, 0, 0);
}

void ESP32Mouse::release(uint8_t b) {
    _buttons &= ~b;
    move(0, 0, 0);
}