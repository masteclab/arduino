int boton;
void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
}

void loop() {
   if (Serial.available()>0){
  boton = (char) Serial.read();
    }

    if (boton == 'I') {
    digitalWrite(3, HIGH);
    delay(100);
    digitalWrite(13,LOW);
    }
    if (boton == 'D')
    {
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(3,LOW);
    }
}
