/*   ~ Simple Arduino - xBee Transmitter sketch ~

  Read an analog value from potentiometer, then convert it to PWM and finally send it through serial port to xBee.
  The xBee serial module will send it to another xBee (resiver) and an Arduino will turn on (fade) an LED.
  The sending message starts with '<' and closes with '>' symbol. 
  
  Dev: Michalis Vasilakis // Date:2/3/2016 // Info: www.ardumotive.com // Licence: CC BY-NC-SA                    */

//Constants: 
const int potPin = A0; //Pot at Arduino A0 pin 
const int potPin1 = A1; //Pot at Arduino A1 pin 
//Variables:
int value ; //Value from pot
int value1 ; //Value from pot
const int threshold = 800;
void setup() {

//Start the serial communication
Serial.begin(9600); //Baud rate must be the same as is on xBee module

}

void loop() {

// if the analog value is high enough, turn on the LED:
value = analogRead(A0);
value1 = analogRead(A1);

if (value > threshold) {
    
//value = analogRead(A0);
//Map the analog value to pwm value
value = map (value, 0, 1023, 0, 255);
//Send the message:
Serial.print('<');  //Starting symbol
Serial.print(value);//Value from 0 to 255
Serial.println('>');//Ending symbol
delay (300);

  } else {
    
//value1 = analogRead(A1);
//Map the analog value to pwm value
value1 = map (value1, 0, 1023, 0, 255);
//Send the message:
Serial.print('<');  //Starting symbol
Serial.print(value1);//Value from 0 to 255
Serial.println('>');//Ending symbol
delay (300);

  }







}
