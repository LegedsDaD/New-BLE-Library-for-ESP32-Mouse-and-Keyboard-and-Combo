#ifndef ESP32_MOUSE_H
#define ESP32_MOUSE_H

#include "ESP32HID.h"

#define MOUSE_LEFT 1
#define MOUSE_RIGHT 2
#define MOUSE_MIDDLE 4

class ESP32Mouse : public ESP32HID {
public:
    void begin(std::string name = "ESP32 Mouse");
    void click(uint8_t b = MOUSE_LEFT);
    void move(int8_t x, int8_t y, int8_t wheel = 0);
    void press(uint8_t b = MOUSE_LEFT);
    void release(uint8_t b = MOUSE_LEFT);

private:
    uint8_t _buttons;
    void sendReport(int8_t x, int8_t y, int8_t wheel);
};

#endif
