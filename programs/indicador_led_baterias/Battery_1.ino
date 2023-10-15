int redLed = 4;
int yellowLed = 3;
int greenLed = 2;

int analogVal = 0;      //almacena el valor que proviene de la batería
float volt = 0;         //salmacena el valor de voltaje calculado
int timeDelay = 1000;   //duración para que los LED permanezcan encendidos

void setup() {
  Serial.begin(9600);
  pinMode(redLed, OUTPUT);    //LED Rojo como Salida
  pinMode(yellowLed, OUTPUT); //LED Amarillo como Salida
  pinMode(greenLed, OUTPUT);  //LED Verde como Salida
}

void loop() {
  analogVal = analogRead(A0);//reads the analog pin value
  volt = 0.0048 * analogVal;//lee el valor del pin analógico
  Serial.println(volt);
  if(volt <= 1.2)//verifica si el voltaje calculado es menor que 1.2 
  digitalWrite(redLed, HIGH);//enciende LED Rojo
  else if(volt > 1.2 && volt < 1.5)//comprueba si el voltaje calculado está entre 1.2 y 1.5 
  digitalWrite(yellowLed, HIGH);//enciende LED Amarillo
  else if(volt >= 1.5)//verifica si el voltaje calculado es mayor que 1.5
  digitalWrite(greenLed, HIGH);//enciende LED Verde

  delay(timeDelay);//duración para que el LED permanezca encendido
  digitalWrite(greenLed, LOW); //apaga el LED Verde
  digitalWrite(yellowLed, LOW);//apaga el LED Amarillo
  digitalWrite(redLed, LOW);   //apaga el LED Verde
  
}
