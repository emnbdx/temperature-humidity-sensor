# Requirements

A running domoticz server with 2 virtual sensors of type Temp+Hum
A ready to flash NodeMCU 1.0 (ESP8266MOD) with 2 DHT22 on port D1 and D2

# How to use

This little sketch is ready to deploy through [Arduino IDE](https://www.arduino.cc/en/software) or [Visual Studio Code with arduino plugin](https://github.com/Microsoft/vscode-arduino)

# What it does

Every 10 seconds NodeMCU connect to wifi, read value on DHT and send data to domoticz devices. I prefer connecting every loop to limit wifi waves !