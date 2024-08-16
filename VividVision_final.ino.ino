#include <ESP8266WiFi.h>
 
String apiKey = "J0AYDNERI9VR37S5";     //  Enter your Write API key from ThingSpeak
 
const char *ssid =  "Niharika";     // replace with your wifi ssid and wpa2 key
const char *pass =  "1234";
const char* server = "api.thingspeak.com";
 
#define S0 D6
#define S1 D7
#define S2 D3
#define S3 D4
#define sensorOut  D5

int frequency1 = 0;
int frequency2 = 0;
int frequency3 = 0;
int colour=0;
 

WiFiClient client;
 
void setup() 
{
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  
  // Setting frequency-scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  Serial.begin(9600);
  delay(10);
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) 
     {
            delay(500);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");
 
}
 
void loop() 
{
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Reading the output frequency
  frequency1 = pulseIn(sensorOut, LOW);
  // Printing the value on the serial monitor
  //Serial.print("R= ");//printing name
  //Serial.print(frequency);//printing RED color frequency
  //Serial.print("  ");
  delay(100);
  // Setting Green filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  frequency2 = pulseIn(sensorOut, LOW);
  // Printing the value on the serial monitor
  //Serial.print("G= ");//printing name
  //Serial.print(frequency);//printing RED color frequency
  //Serial.print("  ");
  delay(100);
  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  frequency3 = pulseIn(sensorOut, LOW);
  // Printing the value on the serial monitor
  //Serial.print("B= ");//printing name
  //Serial.print(frequency);//printing RED color frequency
  //Serial.println("  ");
  delay(100);
  if(frequency1<frequency2 && frequency1<frequency3){
    colour=1;
    Serial.print("Red");
  }
  else if(frequency2<frequency1 && frequency2<frequency3){
    colour=2;
    Serial.print("Green");
  }
  else if(frequency3<frequency1 && frequency3<frequency1){
    colour=3;
    Serial.print("Blue");
  }
  if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
  {  
                            
                             String postStr = apiKey;
                             postStr +="&field1=";
                             postStr += String(colour);
                             //postStr +="&field2=";
                             //postStr += String(h);
                             //postStr += "\r\n\r\n";
 
                             client.print("POST /update HTTP/1.1\n");
                             client.print("Host: api.thingspeak.com\n");
                             client.print("Connection: close\n");
                             client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                             client.print("Content-Type: application/x-www-form-urlencoded\n");
                             client.print("Content-Length: ");
                             client.print(postStr.length());
                             client.print("\n\n");
                             client.print(postStr);
 
                             Serial.print("Colour Code: ");
                             Serial.print(colour);
                             //Serial.print(" degrees Celcius, Humidity: ");
                             //Serial.print(h);
                             Serial.println("%. Send to Thingspeak.");
                        }
          client.stop();
 
          Serial.println("Waiting...");
  
  // thingspeak needs minimum 15 sec delay between updates
  delay(1000);
}