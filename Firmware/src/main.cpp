#include <Arduino.h>
#include "Input.h"
#include "HID.h"

extern volatile bool mcpActionRequired;

static uint32_t lastBatteryUpdate = 0;

extern InputClass input;
extern HIDClass hid;

void setup() {
  input.init();
  hid.init("MacroPad");
}

void loop() {
  if (mcpActionRequired) {
    mcpActionRequired = false;

    InputData packet = input.readHardware();

    hid.sendKeys(packet.keys);

    if (packet.encoderTurned) {
      hid.sendDialTurn(packet.encoderClockwise);
    }

    if (packet.encoderButtonChanged) {
      hid.sendEncoderButton(packet.encoderButtonPressed);
    }
  }

if (millis() - lastBatteryUpdate > 60000) { 
    hid.updateBatteryPercentage(input.getBatteryLevel());
    lastBatteryUpdate = millis();
}
}