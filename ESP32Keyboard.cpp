#include "ESP32Keyboard.h"

// Simplistic ASCII to HID map (Example: 'a' -> 4)
// A full library requires a complete lookup table.
uint8_t asciiToHid(uint8_t k) {
    if (k >= 'a' && k <= 'z') return 4 + (k - 'a');
    if (k >= 'A' && k <= 'Z') return 4 + (k - 'A');
    if (k >= '1' && k <= '9') return 30 + (k - '1');
    if (k == '0') return 39;
    if (k == ' ') return 44;
    if (k == '\n') return 40; // Enter
    return 0;
}

void ESP32Keyboard::begin(std::string name) {
    ESP32HID::begin(name);
}

void ESP32Keyboard::sendReport() {
    // Notify using the KEYBOARD_ID defined in descriptors
    // Note: In strict BLE architecture, we should update the specific characteristic.
    // For this simple wrapper, we update the main input characteristic but use the ID.
    // Actual implementation requires setting the ID if the characteristic supports multiple,
    // or getting the specific characteristic handle.
    // However, NimBLE/BLEDevice usually infers from the value set if setup correctly.

    // IMPORTANT: For proper separation, we get the input report characteristic
    // associated with ID 1.
    this->_hidDevice->inputReport(KEYBOARD_ID)->setValue(_keyReport, 8);
    this->_hidDevice->inputReport(KEYBOARD_ID)->notify();
}

void ESP32Keyboard::sendKey(uint8_t k, uint8_t modifier) {
    _keyReport[0] = modifier;
    _keyReport[1] = 0; // Reserved
    _keyReport[2] = k; // Key 1
    _keyReport[3] = 0;
    _keyReport[4] = 0;
    _keyReport[5] = 0;
    _keyReport[6] = 0;
    _keyReport[7] = 0;
    sendReport();
    delay(10);
    releaseAll();
}

void ESP32Keyboard::releaseAll() {
    memset(_keyReport, 0, 8);
    sendReport();
}

size_t ESP32Keyboard::write(uint8_t k) {
    uint8_t hidCode = asciiToHid(k);
    uint8_t mod = 0;
    if (k >= 'A' && k <= 'Z') mod = 0x02; // Shift

    if (hidCode != 0) {
        sendKey(hidCode, mod);
    }
    return 1;
}

size_t ESP32Keyboard::write(const uint8_t* buffer, size_t size) {
    size_t n = 0;
    while (size--) {
        if (write(*buffer++)) n++;
        else break;
    }
    return n;
}