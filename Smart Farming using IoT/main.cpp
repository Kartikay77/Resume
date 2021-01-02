#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
const char *ssid =  "Galaxy-M20";     // Enter your WiFi Name
const char *pass =  "ac312124"; // Enter your WiFi Password

WiFiClient client;

#define MQTT_SERV "io.adafruit.com"
#define MQTT_PORT 1883
#define MQTT_NAME "choudharyas"
#define MQTT_PASS "988c4e045ef64c1b9bc8b5bb7ef5f2d9"

const int ledPin = D6;
const int ldrPin = D1;
const int moisturePin = A0;             // moisteure sensor pin
const int motorPin = D0;
unsigned long interval = 10000;
unsigned long previousMillis = 0;
unsigned long interval1 = 1000;
unsigned long previousMillis1 = 0;
float moisturePercentage;              //moisture reading

//Set up the feed you're publishing to
Adafruit_MQTT_Client mqtt(&client, MQTT_SERV, MQTT_PORT, MQTT_NAME, MQTT_PASS);
Adafruit_MQTT_Publish AgricultureData = Adafruit_MQTT_Publish(&mqtt,MQTT_NAME "/f/AgricultureData");

//Set up the feed you're subscribing to
 Adafruit_MQTT_Subscribe LED = Adafruit_MQTT_Subscribe(&mqtt, MQTT_NAME "/f/LED");
  Adafruit_MQTT_Subscribe Pump = Adafruit_MQTT_Subscribe(&mqtt, MQTT_NAME "/f/Pump");

void setup()
{
  Serial.begin(115200);
  delay(10);
  mqtt.subscribe(&LED);
  mqtt.subscribe(&Pump);
  pinMode(motorPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(ldrPin, INPUT);
  digitalWrite(motorPin, LOW); // keep motor off initally
  
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");              // print ... till not connected
  }
  Serial.println("");
  Serial.println("WiFi connected");
}
 
void loop()

{
   MQTT_connect();
  

 int ldrStatus = analogRead(ldrPin);

    if (ldrStatus <= 200) {
    
    digitalWrite(ledPin, HIGH);
    
    Serial.print("Its DARK, Turn on the LED : ");
    
    Serial.println(ldrStatus);
    
    } 
    else {
    
    digitalWrite(ledPin, LOW);
    
    Serial.print("Its BRIGHT, Turn off the LED : ");
    
    Serial.println(ldrStatus);
    
    }

  moisturePercentage = ( 100.00 - ( (analogRead(moisturePin) / 1023.00) * 100.00 ) );

 
    Serial.print("Soil Moisture is  = ");
    Serial.print(moisturePercentage);
    Serial.println("%");
    
    

if (moisturePercentage < 35) {
  digitalWrite(motorPin, HIGH);         // tun on motor
}
if (moisturePercentage > 35 && moisturePercentage < 37) {
  digitalWrite(motorPin, HIGH);        //turn on motor pump
}
if (moisturePercentage > 38) {
  digitalWrite(motorPin, LOW);          // turn off mottor
}


if (! AgricultureData.publish(moisturePercentage))
       {                     
         delay(5000);   
          }
Adafruit_MQTT_Subscribe * subscription;
while ((subscription = mqtt.readSubscription(5000)))
     {
    
   if (subscription == &LED)
     {
      //Print the new value to the serial monitor
      Serial.println((char*) LED.lastread);
     
   if (!strcmp((char*) LED.lastread, "OFF"))
      {
        digitalWrite(ledPin, HIGH);
    }
    if (!strcmp((char*) LED.lastread, "ON"))
      {
        digitalWrite(ledPin, LOW);
    }
 }
   
   if (subscription == &Pump)
     {
      //Print the new value to the serial monitor
      Serial.println((char*) Pump.lastread);
     
   if (!strcmp((char*) Pump.lastread, "OFF"))
      {
        digitalWrite(motorPin, HIGH);
    }
     if (!strcmp((char*) Pump.lastread, "ON"))
      {
        digitalWrite(motorPin, LOW);
    }

     }
     }
}
void MQTT_connect() 
{
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) 
  {
    return;
  }

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) // connect will return 0 for connected
  { 
       
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) 
       {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
}
