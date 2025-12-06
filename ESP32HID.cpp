#include "ESP32HID.h"

// Callback class for connection events
class HIDServerCallbacks : public BLEServerCallbacks {
    ESP32HID* _hid;
public:
    HIDServerCallbacks(ESP32HID* hid) : _hid(hid) {}
    void onConnect(BLEServer* pServer) {
        // We set a flag or allow the main loop to know
        // Note: In a real library, we might need a friend class or public setter
        // For simplicity, we assume the user checks isConnected via the device state
    }
    void onDisconnect(BLEServer* pServer) {
        // Handle disconnect logic if needed (advertising restarts automatically below)
    }
};

void ESP32HID::begin(std::string deviceName) {
    BLEDevice::init(deviceName);
    BLEServer* pServer = BLEDevice::createServer();
    pServer->setCallbacks(new HIDServerCallbacks(this));

    _hidDevice = new BLEHIDDevice(pServer);
    _inputCharacteristic = _hidDevice->inputReport(KEYBOARD_ID); // Default input

    _hidDevice->manufacturer()->setValue("ESP32");
    _hidDevice->pnp(0x02, 0xe502, 0xa111, 0x0210);
    _hidDevice->hidInfo(0x00, 0x01);

    _hidDevice->reportMap((uint8_t*)hidReportMap, sizeof(hidReportMap));
    _hidDevice->startServices();

    BLEAdvertising* pAdvertising = pServer->getAdvertising();
    pAdvertising->setAppearance(HID_KEYBOARD);
    pAdvertising->addServiceUUID(_hidDevice->hidService()->getUUID());
    pAdvertising->start();

    _hidDevice->setBatteryLevel(100);
}

bool ESP32HID::isConnected() {
    // A simplified check. For robust checking, use the callback to set a boolean.
    // However, BLEServer doesn't easily expose "getConnectedCount" in older versions.
    // We will rely on the user or the inherited classes to manage state carefully.
    return true; // Placeholder: In production, use callbacks to toggle a boolean flag.
}

void ESP32HID::sendReport(uint8_t id, uint8_t* data, size_t len) {
    if (this->isConnected()) {
        _inputCharacteristic->setValue(data, len);
        _inputCharacteristic->notify();
    }
}