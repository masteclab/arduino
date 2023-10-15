#include <Servo.h>
Servo servo1;
int trigPin = 9;
int echoPin = 8;
long distance;
long duration;
 
void setup() 
{
Serial.begin(9600);
servo1.attach(7); 
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);// put your setup code here, to run once:
}
 
void loop() {
  ultra();
  servo1.write(0);
  if(distance <= 200){ // Es 10, pero lo cambie porque no funcionaba el Ultra
  servo1.write(90);
  }
}
 
void ultra(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration*0.034/2;
  Serial.print(distance);       //Monitorización en centímetros de la distancia en el monitor serial
  Serial.println(" cm"); 
  delay(50);
  }
