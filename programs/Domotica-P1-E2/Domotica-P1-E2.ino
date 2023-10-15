int pulsador=0;               //almacena el estado del botón
void setup() {
Serial.begin(9600);
pinMode(16, INPUT);           //declaramos el pin 16 como entrada
pinMode(5, OUTPUT);
}
void loop() {
pulsador = digitalRead(16);   //lee el estado del botón
if(pulsador==HIGH) {         //si el estado es pulsado
digitalWrite(5, HIGH);     //se apaga el led
delay(1000);
Serial.println("Boton pulsado");
}
else{                        //si el estado es no pulsado
digitalWrite(5, LOW);      //se prende el led
}
}

