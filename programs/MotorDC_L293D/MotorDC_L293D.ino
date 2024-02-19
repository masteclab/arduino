// Program: Puente H Arduino
// Author: jsgutierrez@tecnun.es
// Created: January 25, 2023

// Definición de los pines de control del L293D
int motorPin1 = 8;  // IN1 del L293D
int motorPin2 = 9;  // IN2 del L293D
int enablePin = 10;   // Enable del L293D

void setup() {
  //Pines como salidas
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(enablePin, OUTPUT);
}

void loop() {
  // Hacer girar el motor en una dirección
  digitalWrite(motorPin1, HIGH);  // Configurar el sentido de giro
  digitalWrite(motorPin2, LOW);
  analogWrite(enablePin, 255);     // Controlar la velocidad (0-255)
  delay(1000);                     // 2 seg

  // Hacer girar el motor en dirección opuesta
  digitalWrite(motorPin1, LOW);   // Cambiar el sentido de giro
  digitalWrite(motorPin2, HIGH);
  analogWrite(enablePin, 255);     // Controlar la velocidad (0-255)
  delay(1000);                     // 2 seg

  // Detener el motor
  digitalWrite(motorPin1, LOW);   // Ambos pines de control en bajo
  digitalWrite(motorPin2, LOW);
  analogWrite(enablePin, 0);       // Desactivar el control de velocidad
  delay(1000);                     // 1 seg
}
