#include "ESP32Combo.h"

void ESP32Combo::begin(std::string name) {
    // Initialize the base (Keyboard/HID)
    ESP32Keyboard::begin(name);
}

void ESP32Combo::sendMouseReport(int8_t x, int8_t y, int8_t wheel) {
    uint8_t m[4];
    m[0] = _mouseButtons;
    m[1] = x;
    m[2] = y;
    m[3] = wheel;
    this->_hidDevice->inputReport(MOUSE_ID)->setValue(m, 4);
    this->_hidDevice->inputReport(MOUSE_ID)->notify();
}

void ESP32Combo::mouseMove(int8_t x, int8_t y, int8_t wheel) {
    sendMouseReport(x, y, wheel);
}

void ESP32Combo::mouseClick(uint8_t b) {
    _mouseButtons = b;
    sendMouseReport(0, 0, 0);
    _mouseButtons = 0;
    sendMouseReport(0, 0, 0);
}

void ESP32Combo::mousePress(uint8_t b) {
    _mouseButtons |= b;
    sendMouseReport(0, 0, 0);
}

void ESP32Combo::mouseRelease(uint8_t b) {
    _mouseButtons &= ~b;
    sendMouseReport(0, 0, 0);
}