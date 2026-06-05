#include "HID.h"

HIDClass hid;


const uint8_t hidReportMap[] = {
    0x05, 0x01, 0x09, 0x06, 0xA1, 0x01, 0x85, 0x01,
    0x05, 0x07, 0x19, 0xE0, 0x29, 0xE7, 0x15, 0x00,
    0x25, 0x01, 0x75, 0x01, 0x95, 0x08, 0x81, 0x02,
    0x95, 0x01, 0x75, 0x08, 0x81, 0x01, 0x95, 0x06,
    0x75, 0x08, 0x15, 0x00, 0x25, 0x65, 0x19, 0x00,
    0x29, 0x65, 0x81, 0x00, 0xC0,
    
    // Consumer Volume / Media Control Profile
    0x05, 0x0C, 0x09, 0x01, 0xA1, 0x01, 0x85, 0x02,
    0x09, 0xE9, 0x09, 0xEA, 0x09, 0xE2, 0x15, 0x00,
    0x25, 0x01, 0x75, 0x01, 0x95, 0x03, 0x81, 0x02,
    0x95, 0x01, 0x75, 0x05, 0x81, 0x01, 0xC0
};

void HIDClass::init(const char* deviceName){
    NimBLEDevice::init(deviceName);
    _pServer = NimBLEDevice::createServer();
    _pServer->setCallbacks(new HIDCallbacks());
    _pHid = new NimBLEHIDDevice(_pServer);

    _pHid->setReportMap((uint8_t*)hidReportMap, sizeof(hidReportMap));
    _pHid->setHidInfo(0x00, 0x01);
    _pHid->setPnp(0x02, 0xFFFF, 0x0001, 0x0100);
    _pHid->setManufacturer("Christopher Milewski");
    _pHid->setBatteryLevel(100);
    NimBLEDevice::setSecurityAuth(true, true, true);
    NimBLEDevice::setPower(ESP_PWR_LVL_P9);

    _pInputKey = _pHid->getInputReport(1);
    _pConsumerKey = _pHid->getInputReport(2);

    NimBLEAdvertising* pAdvertizing = NimBLEDevice::getAdvertising();

    _pHid->startServices();

    pAdvertizing->addServiceUUID(_pHid->getHidService()->getUUID());
    pAdvertizing->addServiceUUID("180F");
    pAdvertizing->setAppearance(0x03c1);
    

    pAdvertizing->start();
}

void HIDClass::sendKeys(const bool* keysState) {
    if (_pServer->getConnectedCount() == 0) return;

    uint8_t reportBuffer[8] = {0,0,0,0,0,0,0,0};
    int keyCount = 0;

    const uint8_t hidKeycodes[12] = {
        0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 
        0x5F, 0x60, 0x61, 0x63, 0x62, 0x58
    };

    for (int i=0; i<12; i++) {
        if  (keysState[i] && keyCount < 6){
            reportBuffer[2 + keyCount] = hidKeycodes[i];
            keyCount++;
        }
    }
    _pInputKey->setValue(reportBuffer, sizeof(reportBuffer));
    _pInputKey->notify();
}

void HIDClass::sendDialTurn(bool clockwise) {
    if (_pServer->getConnectedCount() == 0) return;

    uint8_t mediaBuffer = clockwise ? 0x01 : 0x02;
    _pConsumerKey->setValue(&mediaBuffer, 1);
    _pConsumerKey->notify();

    mediaBuffer = 0x00;
    _pConsumerKey->setValue(&mediaBuffer, 1);
    _pConsumerKey->notify();
}

void HIDClass::sendEncoderButton(bool pressed) {
    if (_pServer->getConnectedCount() == 0) return;

    uint8_t mediaBuffer = pressed ? 0x04 : 0x00;
    _pConsumerKey->setValue(&mediaBuffer, 1);
    _pConsumerKey->notify();
}

void HIDClass::updateBatteryPercentage(int percentage){
    if (_pServer->getConnectedCount() == 0) return;
    
    uint8_t batteryPercent = percentage;
    _pHid->setBatteryLevel(batteryPercent);
}