
#include <Servo.h>
int sensor=0;
// Declaramos la variable para controlar el servo
Servo cigarro;

void setup() {
   pinMode (2, INPUT);
  // Iniciamos el servo para que empiece a trabajar con el pin 9
  cigarro.attach(9);

}

void loop() {
 if (digitalRead(2)==LOW){
  while (digitalRead(2)==LOW);
  cigarro.write(180);
  delay(3500);
  cigarro.write(0);
 }
 else
 cigarro.write(0);

 sensor = analogRead(A0);
 sensor= map(sensor, 0, 1023, 0, 255);

if (sensor < 200) {
  while (sensor < 200) {
  sensor= analogRead (A0);
  sensor = map(sensor, 0, 1023, 0, 255);
  }
  cigarro.write(180);
  delay(3500);
  cigarro.write(0);
 }

 else
 cigarro.write(0);
}
