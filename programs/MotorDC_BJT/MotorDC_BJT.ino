// Program: BJT Arduino
// Author: jsgutierrez@tecnun.es
// Created: January 25, 2023

void setup()
{
  Serial.begin(9600);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  
}

void loop()
{
  
  digitalWrite(8, HIGH);
  digitalWrite(7, HIGH);
   Serial.println("1: HIGH");
  
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(8, LOW);
  digitalWrite(7, LOW);
  Serial.println("0: LOW");
  delay(1000); // Wait for 1000 millisecond(s)
}
