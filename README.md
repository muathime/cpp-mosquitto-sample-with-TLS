# Modern mosquitto C++ sample

How to write a C++ MQTT client using Mosquitto The 2022 version.

Read the full article [on my blog](https://thanhphu.net/2018/11/28/how-to-write-a-c-mqtt-client-using-mosquitto/)

#Requirements
(MacOS / Brew) - Linux is similar, replace `brew install` with `sudo apt-get install`
```
brew install mosquitto
brew install libssl-dev
brew install c-ares
```

#Running
Compile and run the code with Make
```
make publish
```