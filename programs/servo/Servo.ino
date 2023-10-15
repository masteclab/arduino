#include <Servo.h>

// Declaramos la variable para controlar el servo
Servo servoMotor;
int contador = 0;
int estado = 0;
void setup() {

  pinMode (2, INPUT);
  // Iniciamos el monitor serie para mostrar el resultado
  Serial.begin(9600);
  // Iniciamos el servo para que empiece a trabajar con el pin 9
  servoMotor.attach(9);
}
 
void loop() {
  estado = digitalRead(2);
  if (estado == LOW){
    contador = contador + 1;
    Serial.print (contador);
    // Desplazamos a la posición 0º
    servoMotor.write(25);
    // Esperamos 1 segundo
    delay(1000);
    
    // Desplazamos a la posición 90º
    servoMotor.write(90);
    // Esperamos 1 segundo
    delay(1000);
  }
  
}
