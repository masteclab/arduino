// Robo India Tutorial 
// Digital Output on LED 
// Hardware: NodeMCU Blynk Board


#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "DHT.h"           // including the library of DHT11 temperature and humidity sensor
//#include <SimpleTimer.h>   //including the library of SimpleTimer
#define DHTTYPE DHT11      // DHT 11

#include <LiquidCrystal_I2C.h>
// Construct an LCD object and pass it the 
// I2C address, width (in characters) and
// height (in characters). Depending on the
// Actual device, the IC2 address may change.
LiquidCrystal_I2C lcd(0x3F, 16, 2);

#define dht_dpin 2
DHT dht(dht_dpin, DHTTYPE); 
//SimpleTimer timer;
char auth[] = "Fw5bFij04k16rDX0MppIsp7n09pfKGam";

// Set password to "" for open networks.
char ssid[] = "INFINITUM449E";
char pass[] = "dxxVxVW3Hd";
float t;                                   // Declare the variables 
float h;

BlynkTimer timer;

void setup()
{
    Serial.begin(9600);// Debug console
    Blynk.begin(auth, ssid, pass);
    dht.begin();
    timer.setInterval(2000, sendUptime);
    lcd.begin(16,2);     // The begin call takes the width and height. This
    lcd.init();          // Should match the number provided to the constructor.
    lcd.backlight();     // Turn on the backlight.
    lcd.setCursor(0, 0); // Move the cursor characters to the right and
                         // zero characters down (line 1).
    lcd.print("Hola");  // Print HELLO to the screen, starting at 0,0.
    
      
    lcd.setCursor(0, 1);    // Move the cursor to the next line and print
    lcd.print("Mundo");     // WORLD.  
    
}

void sendUptime()
{
  
  float h = dht.readHumidity();
  float t = dht.readTemperature(); 
  Serial.println("Humidity and temperature\n\n");
  Serial.print("Current humidity = ");
  Serial.print(h);
  Serial.print("%  ");
  Serial.print("temperature = ");
  Serial.print(t); 
  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);
  
}

void loop()
{

  // ESPERAR ENTRE MEDICIONES, NECESARIO PARA EL BUEN FUNCIONAMIENTO
  delay(2000);
  
  // LEER LA HUMEDAD USANDO EL METRODO READHUMIDITY
  float h = dht.readHumidity();
  // LEER LA TEMPERATURA USANDO EL METRODO READTEMPERATURE
  float t = dht.readTemperature();
 
  // REVISAR QUE LOS RESULTADOS SEAN VALORES NUMERICOS VALIDOS, INDICANDO QUE LA COMUNICACION ES CORRECTA
  if (isnan(h) || isnan(t)) {
    Serial.println("Falla al leer el sensor DHT11!");
    return;
  }
  // IMPRIMIR RESULTADO AL MONITOR SERIAL
  Blynk.run();
  timer.run();
  lcd.setCursor(0, 0);
    lcd.print("Temp:");
  lcd.print(t);
  lcd.println(" \337C    ");
  lcd.setCursor(0, 1);
  lcd.print("Humedad:");
  lcd.print(h);
  lcd.print(" % ");
}
