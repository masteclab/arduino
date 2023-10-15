#include "DHT.h"
// ESTAMOS UTILIZANDO LA TARJETA EXPLORER DE SODAQ
// https://learn.sodaq.com/getting_started/
// https://learn.sodaq.com/Boards/ExpLoRer/
// CONSTRUCTOR DEL OBJETO DHT RECIBE EL PIN EN EL QUE SE CONECTA EL SENSOR
// Y TAMBIEN RECIBE EL TIPO DE SENSOR QUE VAMOS A CONECTAR
DHT dht(2, DHT11);
 
void setup() {
  // PREPARAR LA COMUNICACION SERIAL
  SerialUSB.begin(9600);
  SerialUSB.println("Prueba del sensor DHT11");
  
  // PREPARAR LA LIBRERIA PARA COMUNICARSE CON EL SENSOR
  dht.begin();
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
    SerialUSB.println("Falla al leer el sensor DHT11!");
    return;
  }
 
  // IMPRIMIR RESULTADO AL MONITOR SERIAL
  //SerialUSB.print("Humedad: ");
  //SerialUSB.print(h);
  //SerialUSB.print(" % ");
  //SerialUSB.print("Temperatura: ");
  SerialUSB.print(t);
  //SerialUSB.println(" °C");
}
