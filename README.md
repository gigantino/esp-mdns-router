# esp-mdns-router

 [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

This project allows for wireless data exchange between two ESP boards without external WiFi support. It uses a master ESP32 Dev Board and a slave Wemos D1 with ESP8266 for data exchange. The solution works effectively with multiple slave boards depending on the application.

> Note: You are free to use other compatible ESP boards depending on your need by changing the platformio.ini file accordingly. Keep in mind that different boards use different libraries for wireless communication (e.g. the ESP32 uses WiFi.h, while the ESP8266 uses ESP8266WiFi.h)

The master board starts it's own access point (configurable in **/include/secrets.h**) and uses the mDNS protocol to create a local domain name (by default **master.local**) to simplify the connection between boards. Not all boards are compatible with mDNS, reason for which you should be able to access the master using the IP address 192.168.1.4 or by setting your own static one.


##  Usage
This whole project is meant to be used with [VSCode](https://code.visualstudio.com/) and the [PlatformIO](https://platformio.org). It is possible to make it work along with the Arduino IDE, but I wouldn't recommend it.

If you already have everything installed you should be set to go. In the **platformio.ini** you can configure every setting according to your needs (like the upload port, baud rate and board).

Also note that if you are getting any errors, you probably didn't select the right environment from the bottom. 
