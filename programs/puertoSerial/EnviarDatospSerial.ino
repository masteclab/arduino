
int contador;
void setup( )  
{  
Serial.begin(9600);  
}  

void loop( )  
{  
delay(3000);

for (int i=48; i<57; i++)
{
  if (contador=i){
    contador= contador+1;
    delay(5000);
    Serial.write(contador); 
  }
}

}
