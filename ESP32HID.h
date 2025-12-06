#ifndef ESP32_HID_H
#define ESP32_HID_H

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLEHIDDevice.h>
#include <BLE2902.h>
#include "HIDDescriptors.h"

class ESP32HID {
public:
    void begin(std::string deviceName = "ESP32 HID");
    bool isConnected();

    // Internal access for child classes
    void sendReport(uint8_t id, uint8_t* data, size_t len);

protected:
    BLEHIDDevice* _hidDevice;
    BLECharacteristic* _inputCharacteristic;
    bool _connected = false;

private:
    static void taskServer(void* pvParameter);
};

#endif#
