#ifndef HID_H
#define HID_H

#include <Arduino.h>
#include "NimBLEDevice.h"
#include "NimBLEHIDDevice.h"

class HIDClass {
    private:
        NimBLEServer*          _pServer = nullptr;
        NimBLEHIDDevice*       _pHid = nullptr;
        NimBLECharacteristic*  _pInputKey = nullptr;
        NimBLECharacteristic*  _pConsumerKey = nullptr;
    
    public:
        void init(const char* deviceName);
        void sendKeys(const bool* keysState);
        void sendDialTurn(bool clockwise);
        void sendEncoderButton(bool pressed);
        void updateBatteryPercentage(int percentage);
};

class HIDCallbacks : public NimBLEServerCallbacks {
public:
    void onDisconnect(NimBLEServer* pServer, NimBLEConnInfo&, int) override {
        pServer->getAdvertising()->start();
    }
};

#endif
