#include "DHT.h"
#include <ESP8266WiFi.h>

String api_key = "B446IHNIAQOD23RA";     //  Enter your Write API key from ThingSpeak
const char *ssid =  "INFINITUM449E";     // replace with your wifi ssid and wpa2 key
const char *pass =  "dxxVxVW3Hd";
const char* server = "api.thingspeak.com";

#define DHTTYPE DHT11      // DHT 11

#define dht_dpin 2
DHT dht(dht_dpin, DHTTYPE); 

WiFiClient client;
 
void setup() 
{
       Serial.begin(115200);
       delay(10);
       pinMode(2, OUTPUT);
       digitalWrite(2, 0);
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
     // int chk = dht.read11(DHTPIN);
      float h = dht.readHumidity();
      float t = dht.readTemperature();
      
              if (isnan(h) || isnan(t)) 
                 {
                     Serial.println("Failed to read from DHT sensor!");
                      return;
                 }

               if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
            {  
                   String data_to_send = api_key;
                    data_to_send += "&field1=";
                    data_to_send += h;
                    data_to_send += "&field2=";
                    data_to_send += t;
                    data_to_send += "\r\n\r\n";

                   client.print("POST /update HTTP/1.1\n");
                   client.print("Host: api.thingspeak.com\n");
                   client.print("Connection: close\n");
                   client.print("X-THINGSPEAKAPIKEY: " + api_key + "\n");
                   client.print("Content-Type: application/x-www-form-urlencoded\n");
                   client.print("Content-Length: ");
                   client.print(data_to_send.length());
                   client.print("\n\n");
                   client.print(data_to_send);
                   delay(1000);
                   Serial.print("Temperature: ");
                   Serial.print(t);
                   Serial.print(" degrees Celcius, Humidity: ");
                   Serial.print(h);
                   Serial.println("%. Send to Thingspeak.");
              }
          client.stop();
 
          Serial.println("Waiting...");
  
  // thingspeak needs minimum 15 sec delay between updates, i've set it to 30 seconds
  delay(10000);
}
