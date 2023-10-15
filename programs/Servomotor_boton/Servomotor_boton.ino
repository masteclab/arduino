#include <Servo.h>

Servo servo_9;
Servo servo_10;

const int buttonPin_2 = 2;
const int buttonPin_3 = 3;
int val;
int buttonState = 0;

void setup()
{
  servo_9.attach(9);
  servo_10.attach(10);
  pinMode(buttonPin_2, INPUT);      
  pinMode(buttonPin_3, INPUT);     
}

void loop()
{
  buttonState = digitalRead(buttonPin_2);
  if (buttonState == HIGH) {     
    val = 90; 
  }
  else {
    val = 0;
  }
  servo_9.write(val);
  delay(15);


  buttonState = digitalRead(buttonPin_3);
  if (buttonState == HIGH) {     
    val = 170; 
  }
  else {
    val = 0;
  }
  servo_10.write(val);
  delay(15);
  
}
