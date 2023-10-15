const int Led13=13;
const int Led12=12;
const int Led11=11;

int data;

void setup() {
  Serial.begin(9600);
  pinMode(Led13, OUTPUT);
  pinMode(Led12, OUTPUT);
  pinMode(Led11, OUTPUT);
}

void loop() {
  if(Serial.available()){
    data=Serial.read();
    
    if(data=='A'){
      digitalWrite(Led13, HIGH);
    }
    else{
      digitalWrite(Led13,LOW);
    }
    delay(50);

    if(data=='B'){
      digitalWrite(Led12, HIGH);
    }
    else{
      digitalWrite(Led12,LOW);
    }
    delay(50);


    if(data=='C'){
      digitalWrite(Led11, HIGH);
    }
    else{
      digitalWrite(Led11,LOW);
    }
    delay(50);

    if(data=='F'){
      digitalWrite(Led13,LOW);
      digitalWrite(Led12,LOW);
      digitalWrite(Led11,LOW);
    }
    delay(50);
    
  }

}
