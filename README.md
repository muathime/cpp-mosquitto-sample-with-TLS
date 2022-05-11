# Modern mosquitto C++ sample

How to write a C++ MQTT client using Mosquitto The 2022 version.

Read the original article in C [on thanhphu's blog](https://thanhphu.net/2018/11/28/how-to-write-a-c-mqtt-client-using-mosquitto/)

#Requirements
(Linux / apt ) - MacOs is similar, replace `sudo apt-get install` with `brew install`
```
sudo apt-get install mosquitto
sudo apt-get install libssl-dev
sudo apt-get install libmosquitto-dev
sudo apt-get install c-ares
```

#Running
Compile and run the code with Make
```
make publish
```