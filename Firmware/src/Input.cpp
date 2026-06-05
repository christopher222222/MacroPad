#include "Input.h"

Adafruit_MCP23X17 mcp;
InputClass input;

volatile bool mcpActionRequired = false;

ICACHE_RAM_ATTR void handleMcpInterrupt() { mcpActionRequired = true; }


void InputClass::init(){
    mcp.begin_I2C(0x20);

    pinMode(INTERRUPT_PIN, INPUT);
    pinMode(BATTERYSENSE_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), handleMcpInterrupt, FALLING);

    mcp.setupInterrupts(true, false, LOW);

    for (uint16_t i = 0; i <= 14; i++){
        mcp.pinMode(i, INPUT_PULLUP);
        mcp.setupInterruptPin(i, CHANGE);
    }

    _lastEncoderA = mcp.digitalRead(12);
    _lastEncoderButton = (mcp.digitalRead(14) == LOW);
    mcp.clearInterrupts();
}

InputData InputClass::readHardware() {
    InputData data{};

    uint32_t now = millis();

    if (now - _lastDebounceTime < 25){
        mcp.clearInterrupts();
        return data;
    }
    _lastDebounceTime = now;

    for (uint16_t i = 0; i < 12; i++) {
        _keys[i] = (mcp.digitalRead(i) == LOW);
        data.keys[i] = _keys[i];
    }
    
    bool currentA = mcp.digitalRead(12);
    bool currentB = mcp.digitalRead(13);

    if(currentA != _lastEncoderA){
        data.encoderTurned = true;
        data.encoderClockwise = (currentA == currentB);
    }
    _lastEncoderA = currentA;

    bool currentBtn = (mcp.digitalRead(14) == LOW);
    if (currentBtn != _lastEncoderButton) {
        data.encoderButtonChanged = true;
        data.encoderButtonPressed = currentBtn;
    }
    _lastEncoderButton = currentBtn;

    mcp.clearInterrupts();
    return data;
}

int InputClass::getBatteryLevel(){
    int mv = analogReadMilliVolts(BATTERYSENSE_PIN);
    if (mv < 500) {
        return 100;
    } else {
        return constrain(map((mv * 2), 3300, 4200, 0, 100), 0, 100);
    }
}