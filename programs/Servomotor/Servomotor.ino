#include <Servo.h>
int servo = 0;
Servo servo_1;
int counter;

void setup() {
  servo_1.attach(7);
  Serial.begin(9600);
}

void loop() {
  servo_1.write(0);
  delay(1000);
  servo_1.write(45);
  delay(1000);
  servo_1.write(90);
  delay(1000);
  servo_1.write(120);
  delay(1000);
  servo_1.write(160);
  delay(1000);
}
