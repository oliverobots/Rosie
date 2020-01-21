# Rosie

Rosie is a robot dedicated to detecting when your washing machine or dryer has completed its cycle. Rosie, who runs off of an ESP 8266 WiFi chip, periodically collects reading from an MPU-6050 Accelerometer/Gyro Sensor and sends them off to a dedicated server for further processing, sending notifications, or anything you'd like.

## Sensor Setup

### Hardware

* ESP 8266 WiFi Module (Smaller 8-Pin Module)
* MPU-6050 Gyro/Accelerometer Sensor Module
* 3.3V DC Source

### ESP 8266 Pin Connections

| Pin   | Connection       |
| :---: |:----------------:|
|  3V3  | 3.3 VDC Power    |
|  RX   | N/A              |
|  RST  | N/A              |
|  IO0  | MPU-6050 SCL Pin |
|  EN   | 3.3 VDC Power    |
|  IO2  | MPU-6050 SDA Pin |
|  TX   | 3.3 VDC Power    |
|  GND  | Ground           |

### MPU-6050 Pin Connections

| Pin   | Connection       |
| :---: |:----------------:|
|  VCC  | 3.3 VDC Power    |
|  GND  | Ground           |
|  SCL  | ESP 8266 IO0 Pin |
|  SDA  | ESP 8266 IO2 Pin |
|  XDA  | N/A              |
|  XCL  | N/A              |
|  AD0  | N/A              |
|  INT  | N/A              |

### Before Flashing

Modify SSID & Password to correct WiFi credentials.

Also, modify host IP & Port to match the address of the Server.

### Flashing Firmware

Firmware is flashed using an Arduino UNO. [See This Tutorial](https://ubidots.com/blog/esp8266-arduino-ide-tutorial/)

When flashing new firmware, Modify the above pinout as follows:

* Add TX <-> TX & RX <-> RX connections between ESP 8266 & Arduino
* Connect Arduino GND to rest of circuit GND
* Move IO0 connection to Arduino GND
* Connect Arduino RST Pin to GND

*Note: Arduino 3.3V does not seem to source enough power for the ESP 8266.*

Best results have been obtained following this strategy:

1. Disconnect 3.3V Power Source
1. Plug in Arduino via USB
1. Start uploading firmware
1. While firmware is being uploaded, re-connect 3.3V Power Source

*Note: ESP 8266 may fail to connect for multiple reasons - unsure why, disconnecting power and trying again seems to eventually work.*

## Server Setup

### Before Running

At the bottom of the file specify IP Address & Port for the server (should match where firmware is set to POST)
