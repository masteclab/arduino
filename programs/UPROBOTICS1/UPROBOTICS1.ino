int t=0;

void setup() {

pinMode(2, OUTPUT); // configura el 'pin' como salida

}


void loop() {

digitalWrite(13, HIGH); // pone el ‘pin’ en estado alto
delay(t);
digitalWrite(13, LOW);
delay(t);
t += 10; // t = t + 10
}
