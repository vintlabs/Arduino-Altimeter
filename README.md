# Arduino-Altimeter
Read Pressure and Temperature on Arduino from MS5607 device to get Altitude
Information can be read via serial to PC or on an Android device using an HC-05 Bluetooth module


# NOTE: This device is 3.3V ONLY. Do *NOT* use with a 5v Arduino!

# Also note: This is for informational use only, and not to be used in safety critical applications.


## DEPENDENCIES:
arduino-ms5xxx Library: https://github.com/Schm1tz1/arduino-ms5xxx

## Usage:
To use in human-readable serial mode, in Arduino-Altimeter.ino set:
`#define USE_BLUETOOTH false`
To use with an HC-05 (or other) serial Bluetooth transceiver set to `true`

![MS5670 Example Application](https://github.com/pvint/Arduino-Altimeter/blob/master/images/Arduino-MS5607-HC05.png?raw=true)
Example with `#define USE_BLUETOOTH true` (`true` uses JSON output, `false` produces human-readable output)
![MS5670 Serial JSON Output](https://github.com/pvint/Arduino-Altimeter/blob/master/images/ConsoleOutputJSON.png?raw=true)


## Android App:
The supplied app is very basic but handy for simple usage and testing.
To use:
- Install the BT_Alt.apk
- Ensure that Arduino-Altimeter is compiled and installed with `#define USE_BLUETOOTH true`
- Pair the HC-05
- Start the App
- Press "Connect" and select your BT device (normally HC-05)
- To get relevant altitude information, simply press "Set" to set current altitude as reference, or alternately enter a reference barometric pressure in kPa

Note: The Android app does some smoothing on the altitude figure, thus the altitude figure is likely to fluctuate much more on the serial console than the value displayed on the Android app.

![Android Screenshot](https://github.com/pvint/Arduino-Altimeter/blob/master/images/AndroidExample.png?raw=true)


