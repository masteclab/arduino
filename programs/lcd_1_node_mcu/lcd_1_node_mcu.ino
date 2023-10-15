
#include "DHT.h"
DHT dht(2, DHT11);
#include <LiquidCrystal_I2C.h>
// Construct an LCD object and pass it the 
// I2C address, width (in characters) and
// height (in characters). Depending on the
// Actual device, the IC2 address may change.
LiquidCrystal_I2C lcd(0x3F, 16, 2);

void setup() {
 dht.begin();
 lcd.begin(16,2);     // The begin call takes the width and height. This
 lcd.init();          // Should match the number provided to the constructor.
 lcd.backlight();     // Turn on the backlight.
 lcd.setCursor(0, 0); // Move the cursor characters to the right and
                      // zero characters down (line 1).
 lcd.print("Hola");  // Print HELLO to the screen, starting at 0,0.

  
 lcd.setCursor(0, 1);    // Move the cursor to the next line and print
 lcd.print("Mundo");     // WORLD.  
  }

 
void loop() {
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
  lcd.setCursor(0, 0);
  lcd.print("Humedad:");
  lcd.print(h);
  lcd.print(" % ");
  lcd.setCursor(0, 1);
  lcd.print("Temp:");
  lcd.print(t);
  lcd.println(" 'C    ");
}
