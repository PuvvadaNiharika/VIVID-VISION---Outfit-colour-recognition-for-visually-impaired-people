# VIVID-VISION---Outfit-colour-recognition-for-visually-impaired-people


# ESP8266 Color Sensor with ThingSpeak Integration

This project demonstrates how to use an ESP8266 microcontroller to read color frequencies using a TCS3200 color sensor and upload the detected color data to ThingSpeak. The code connects the ESP8266 to a Wi-Fi network, detects the color, and sends the data to ThingSpeak.

## Components

- ESP8266 (NodeMCU or similar)
- TCS3200 Color Sensor
- Wi-Fi Network
- ThingSpeak Account

## Wiring Diagram

| TCS3200 Pin  | ESP8266 Pin |
|--------------|-------------|
| S0           | D6          |
| S1           | D7          |
| S2           | D3          |
| S3           | D4          |
| OUT          | D5          |
| VCC          | 3.3V        |
| GND          | GND         |

## Code Explanation

### Wi-Fi Configuration
Set up your Wi-Fi SSID and password in the following section:

```cpp
const char *ssid =  "Your_SSID";     
const char *pass =  "Your_PASSWORD";


String apiKey = "MRCLWXFGDVRCUKE5"; 

#define S0 D6
#define S1 D7
#define S2 D3
#define S3 D4
#define sensorOut  D5

if(frequency1 < frequency2 && frequency1 < frequency3) {
    colour = 1;  // Red
} else if(frequency2 < frequency1 && frequency2 < frequency3) {
    colour = 2;  // Green
} else if(frequency3 < frequency1 && frequency3 < frequency2) {
    colour = 3;  // Blue
}



if (client.connect(server, 80)) {
    String postStr = apiKey;
    postStr += "&field1=";
    postStr += String(colour);
    
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: " + String(postStr.length()) + "\n\n");
    client.print(postStr);
    Serial.println("Color sent to ThingSpeak.");
}
