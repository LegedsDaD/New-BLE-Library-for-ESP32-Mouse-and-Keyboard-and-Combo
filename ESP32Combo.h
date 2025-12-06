#ifndef ESP32_COMBO_H
#define ESP32_COMBO_H

#include "ESP32Keyboard.h"
#include "ESP32Mouse.h"

// Inherit from both (Multiple Inheritance)
// Note: This requires virtual inheritance in base classes to avoid "Diamond Problem"
// with ESP32HID. For this simpler implementation without modifying base structure heavily, 
// we will compose them or simply inherit Keyboard and add Mouse functionality.

// Simplified Combo Approach:
// We create a class that exposes both sets of functionality.
class ESP32Combo : public ESP32Keyboard {
public:
    void begin(std::string name = "ESP32 Combo");

    // Mouse functions wrapped here
    void mouseMove(int8_t x, int8_t y, int8_t wheel = 0);
    void mouseClick(uint8_t b = 1);
    void mousePress(uint8_t b = 1);
    void mouseRelease(uint8_t b = 1);

private:
    uint8_t _mouseButtons = 0;
    void sendMouseReport(int8_t x, int8_t y, int8_t wheel);
};

#endif
