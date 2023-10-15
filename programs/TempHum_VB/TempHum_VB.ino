#include "DHT.h"
 
// CONSTRUCTOR DEL OBJETO DHT RECIBE EL PIN EN EL QUE SE CONECTA EL SENSOR
// Y TAMBIEN RECIBE EL TIPO DE SENSOR QUE VAMOS A CONECTAR
DHT dht(2, DHT11);
 
void setup() {
  // PREPARAR LA COMUNICACION SERIAL
  Serial.begin(9600);
  Serial.println("Prueba del sensor DHT11");
    //foco
   pinMode(7,OUTPUT);
//ventilador
  pinMode(9,OUTPUT);
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
    Serial.println("Falla al leer el sensor DHT11!");
    return;
  }


  //Serial.print("Temperatura: ");
  Serial.print(t,0);
  //Serial.print(" *C ");

  if (t<28) {
    digitalWrite(7,HIGH);
    digitalWrite(9,LOW);
  }
  else {
    if (t>28){
      digitalWrite(7,LOW);
      digitalWrite(9,HIGH);
    }
   else {
    digitalWrite(7,LOW);
    digitalWrite(9,LOW);
   }
  }

 
  // IMPRIMIR RESULTADO AL MONITOR SERIAL
  //Serial.print("Humedad: ");
//Serial.print(h,0);
  //Serial.print(" %");
  //Serial.print("Temperatura: ");
  //Serial.print(t);
  //Serial.println(" °C");
}
