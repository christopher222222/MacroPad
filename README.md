# Full-Suite MacroPad
The Full-Suite MacroPad is a configurable macropad that incorporates Cherry MX key switches, a rotary encoder, and a 2" IPS screen that can display anything.
### Features

 - 2" IPS Display for displaying data and images (firmware support coming soon)
 - 12 Cherry MX Keyswitches
 - One Mechanical Rotary Encoder with Full Customization
 - 2000Mah Lipo Battery With Charging Circuit and Charge Sensing
 - Bluetooth Low Energy Wireless Connectivity With HID, Configuration, and Image Streaming Support (configuration and image streaming firmware support coming soon)
 - Full Low Latency NKRO (N-Key Rollover) Using MCP23017 I2C IO Expander

## CAD Model
This case uses an unconventional method of mounting by sliding from sides of the PCB to notches on the sides of the Front Case. After that, the case can now be fully assembled from 2 M3x5x4 heatset inserts and 2 M3x8 SHCS screws.
![MacroPad Render](https://raw.githubusercontent.com/christopher222222/MacroPad/refs/heads/main/Images/MacroPad%20Render.png)
Made in Onshape, Rendered in Blender.
## PCB and Schematic
The PCB and Schematic were both designed in EasyEDA Pro.
### Schematic
![MacroPad Schematic](https://raw.githubusercontent.com/christopher222222/MacroPad/refs/heads/main/Images/MacroPad%20Schematic.png)

### PCB
![MacroPad PCB](https://raw.githubusercontent.com/christopher222222/MacroPad/refs/heads/main/Images/MacroPad%20PCB.png)
(Tung for protection)
## Firmware
The firmware was an alternative approach to the regular QMK Firmware. It utilizes PlatformIO with the Arduino Framework and uses an object-oriented structure. The Bluetooth Low Energy data transfer including HID is handled via NimBLE as it is a very lightweight package. The data reading from the MCP23017 uses a common Adafruit library as it simplifies much of the code.
## Bill of Materials
|Item|Quantity|
|--|--|
| Seeed Xiao ESP32-C3 |1|
|MCP23017 I2C IO Expander|1|
|SK-12E12-G070 Slide Switch|1|
|S2B-PH-K-S 90° Angle JST PH Connector|1|
|Lithium Ion Battery - 2000Mah with JST PH Connector|1|
|Adafruit 2" IPS TFT Display|1|
|Cherry MX Keyswitch|12|
|DSA Keycaps Sanded to > 15.6mmx15.6mm|12|
|EC11 Mechanical Rotary Encoder|1|
|1/4W 100KΩ Resistor|2|
|1/4W 4.7KΩ Resistor|2|
|1/4W 10KΩ Resistor|1|
|16V 100nF Ceramic Capacitor|1|
|M3x5x4 Heatset Inserts|2-6|
|M3x8 SHCS Screw*|2|
|3D Printed Front Case|1|
|3D Printed Back Case|1|
|3D Printed Encoder Knob|1|
*SHCS screws can be swapped with BHCS

