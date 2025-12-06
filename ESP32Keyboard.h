#ifndef ESP32_KEYBOARD_H
#define ESP32_KEYBOARD_H

#include "ESP32HID.h"
#include "Print.h"

const uint8_t KEY_LEFT_CTRL = 0x80;
const uint8_t KEY_LEFT_SHIFT = 0x81;
const uint8_t KEY_LEFT_ALT = 0x82;
const uint8_t KEY_LEFT_GUI = 0x83;
const uint8_t KEY_RETURN = 0xB0;
const uint8_t KEY_ESC = 0xB1;
const uint8_t KEY_BACKSPACE = 0xB2;
const uint8_t KEY_TAB = 0xB3;

class ESP32Keyboard : public ESP32HID, public Print {
public:
    void begin(std::string name = "ESP32 Keyboard");

    void sendKey(uint8_t k);
    void sendKey(uint8_t k, uint8_t modifier);
    void releaseAll();

    // Print class implementation for "typing" strings
    virtual size_t write(uint8_t k);
    virtual size_t write(const uint8_t* buffer, size_t size);

private:
    uint8_t _keyReport[8];
    void sendReport();
};

#endif
