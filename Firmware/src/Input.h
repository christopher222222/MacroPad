#ifndef INPUT_H
#define INPUT_H

#include "Adafruit_MCP23X17.h"
#include <Arduino.h>

#define INTERRUPT_PIN D7
#define BATTERYSENSE_PIN D2

struct InputData {
    bool keys[12];
    bool encoderTurned;
    bool encoderClockwise;
    bool encoderButtonChanged;
    bool encoderButtonPressed;
};

class InputClass {
    private:
        bool _keys[12]{};
        bool _lastEncoderA = HIGH;
        bool _lastEncoderButton = false;
        unsigned long _lastDebounceTime = 0;

    public:
        void init();
        InputData readHardware();
        int getBatteryLevel();
};

#endif