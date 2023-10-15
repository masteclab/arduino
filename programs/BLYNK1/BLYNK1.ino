#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>  
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "db232f6b20c84056a8dc531e0907abb7";
//char ssid[] = "INFINITUM7663FD";
//char pass[] = "EF14D0DC6C";

char ssid[] = "AlumnosUP";
char pass[] = "";

//char ssid[] = "iPhone de SEBASTIAN";
//char pass[] = "4499783398";

/* HC-SR501 Motion Detector */
#define ledPin D7 
#define pirPin D1 // Input for HC-S501
int pirValue; // Place to store read PIR Value

void setup()
{
  Serial.begin(9600);
  delay(10);
  Blynk.begin(auth, ssid, pass);
  pinMode(ledPin, OUTPUT);
  pinMode(pirPin, INPUT);
  digitalWrite(ledPin, LOW);
}

/***************************************************
 * Get PIR data
 **************************************************/
void getPirValue(void)
{
  pirValue = digitalRead(pirPin);
  if (pirValue) 
  { 
    Serial.println("==> Motion detected");
    //Blynk.notify("T==> Motion detected");
    //Blynk.tweet("Motion detected in The Energy Lab\n #IoT #TecnologíasEnergéticas #EnergyLab @TecnologiasUP @mecatronicaUP");
  }
  digitalWrite(ledPin, pirValue);
}

void loop()
{
  getPirValue();
  Blynk.run();
}

