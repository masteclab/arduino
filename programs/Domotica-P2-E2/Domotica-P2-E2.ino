#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <aREST.h>

#define LED 5 // Se define el GPIO5 o PIN D1 del NodeMCU ESP8266 como indicador LED
#define LEDW 4 // Se define el GPIO4 o PIN D2 del NodeMCU ESP8266 como indicador LED
int valor = 1; // Creamos una variable que la usaremos para un contador

char* device_id = "87fcfc"; //Recuerda que no debió de hber sido de más de 8 caracteres alfanumericos
char* event = "esp8266";//Evento

//char * key = "mvit337hvw6xoqfl";

//#include "configHOME.h" // Casa de Sebastián

#include "configUP.h" // Casa de Sebastián

//Estas son funciones que usan las librerias especiales de PubSubClient y aREST
//Estas librerías son especiales, por lo que no son sentencias de código estándar
//Sino que solo sirven para este ejemplo con la plataforma de aREST
WiFiClient espClient;
PubSubClient client(espClient);
aREST rest = aREST(client);


void callback(char* topic, byte* payload, unsigned int length); // Declaramos una función especial de la libreria de aREST

void setup(void)
{
  // Iniciamos la lectura del puerto serial
  Serial.begin(115200);
  delay(200);
  Serial.println();
  delay(10); // delay corto para empezar a leer el puerto serial

  client.setCallback(callback); // Esta es una función especial de la librería de aREST
  rest.set_id(device_id); // Esta es una función especial de la librería de aREST que le indica el identificador especial
  rest.set_name(event); // Esta es una función especial de libreria  de aREST que le indica el nombre que le pondremos al "evento"

  //pinMode(LED,OUTPUT); // Declaramos que el pin D1 es de salida
  pinMode(LEDW,OUTPUT); // Declaramos que el pin D2 es de salida
  //digitalWrite(LED,LOW); // El estado del LED está apagado
  digitalWrite(LEDW,LOW); // El estado del LED está apagado

  // Conexión a la red WiFi
  Serial.println();
  Serial.println();
  Serial.println("Conectándose a la red:  ");
  Serial.println(ssid);
  unsigned long startTime = millis();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED && startTime + 30 * 1000 >= millis()) {
    delay(500);
    Serial.print(".");
  }
  if (WiFi.status() == WL_CONNECTED)
  {
    while (valor<5){ // la función while hace la siguiente sentencia, repite el ciclo que hay entre {} hasta que se cumpla la condicion de valor=5
    digitalWrite(LEDW,HIGH);
    delay(500);
    digitalWrite(LEDW,LOW);
    delay(500);
    valor++;
    }
    Serial.println("");
    Serial.println("Red WiFi Conectada!!");
    Serial.println("Direccion IP: ");
    Serial.println(WiFi.localIP());
  }
  else
  {
    WiFi.disconnect();
    Serial.println("");
    Serial.println("Tiempo de espera de conexión a WiFi terminado... intentarlo más tarde!!!");
  }

  char* out_topic = rest.get_topic(); //en la variable out_topic alojaremos la cadena de caracteres de una función especial de aREST

}

void loop() {
  // La única sentencia que necesitamos que se aloje indefinidamente en nuestra placa es 
  // es una función especial de la libreria de aREST que manda llamar el servicio en la nube
  // que nos permitirá conectarnos a nuestro dispositivo desde cualqueir parte del mundo
  // a través de la red de internet.
  rest.loop(client);
}

// Esta función extra al loop va fuera del mismo ya que solo se manda llamar cuando
// se hace falta.
void callback(char* topic, byte* payload, unsigned int length) {
  rest.handle_callback(client, topic, payload, length);
}
