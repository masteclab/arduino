#include <ESP8266WiFi.h>    
#include <PubSubClient.h>
#include <aREST.h>
#include <arduino.h>

// Definimos la salida del Led y la entrada del BOTÓN
#define BT 16 // Se define el GPIO16 o Pin D0 del NodeMCU ESP8266 como la entrada de lectura del botón
#define LED 5 // Se define el GPIO5 o PIN D1 del NodeMCU ESP8266 como indicador LED

// Nos permite leer la Red de Internet y la Clave
//#include "configHOME.h" // Casa de Sebastián
#include "configUP.h" //Universidad

// Definimos los parámetros para el IFTTT
#define HOSTIFTTT "maker.ifttt.com"
#define EVENT "Boton"
#define IFTTTKEY "d4DIw4rLyCtKs1sg5SsfHy"
const int httpsPort = 443;


// Variables
WiFiClientSecure client;


// Function prototypes
void sendWebRequest(void);

// Valores iniciales
int LecturaBT = LOW; // Creamos una variable iniciada en LOW
int valor = 0; 

void setup() {
  Serial.begin(115200);
  delay(200);
  Serial.println();
  delay(10); // delay corto para empezar a leer el puerto serial
  
  pinMode(BT, INPUT);
  pinMode(LED,OUTPUT);
  digitalWrite(LED,HIGH); // El estado del LED está apagado

   // Conexión a la red WiFi
  Serial.println();
  Serial.println();
  Serial.println("Conectandose a la red:  ");
  Serial.println(ssid);
  unsigned long startTime = millis();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED && startTime + 30 * 1000 >= millis()) {
    delay(500);
    Serial.print(".");
  }
  if (WiFi.status() == WL_CONNECTED)
  {
    digitalWrite(LED,HIGH);
    delay(500);
    digitalWrite(LED,LOW);
    delay(500);
    digitalWrite(LED,HIGH);
    delay(500);
    digitalWrite(LED,LOW);
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
}


void loop() {
   LecturaBT = digitalRead(BT);
    if (LecturaBT == LOW) // Es importante colocar una resistencia de al menos 10k-ohms a GND para mantener el estado inicial y de cambio en 0 (LOW) 
    {                     
       if (valor == 1){
       Serial.println("Enviar SMS");
       digitalWrite(LED,HIGH);  // Se prende el LED
       WiFiClient client; // Nos preparamos para hacer conexión con el servicio en internet
       if (!client.connect(HOSTIFTTT, 80)) // Realizamos un comparación, Si no se puede hacer la conexión por el puerto 80 (internet) a servicio de IFTTT... 
       {
        Serial.println("No se puede hacer la conexion al canal de IFTTT solicitado");
        digitalWrite(LED,LOW);  // Se apaga el LED
       return;
       }
       
       Serial.println("Conectandose a IFTTT...");
       // Ahora hacemos la acción Request del servicio en IFTTT, para obtner más info de esta petición revisa la documentacion de IFTTT
      sendWebRequest();
      }

       delay(3000);
       Serial.println("Servicio de IFTTT exitoso!!");
       Serial.println("El servicio listo para una nueva peticion");
       digitalWrite(LED,LOW);  // Se apaga el LEd una vez hecho el servicio
       }
    
    else{
    valor = 1;
    delay(500);
    }
}

void sendWebRequest() {
  Serial.print("Entrando a ");
  Serial.println(HOSTIFTTT);

  if (!client.connect(HOSTIFTTT,httpsPort)) {
    Serial.println("Mala conexion");
    return;
  }

  // Make a URL
  // maker.ifttt.com/trigger/{event}/with/key/{key}
  String url = "/trigger/";
  url += EVENT;
  url += "/with/key/";
  url += key;

  Serial.print("requesting URL: ");
  Serial.println(url);

  // Send a web request
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + HOSTIFTTT + "\r\n" +
               "Connection: close\r\n\r\n");

  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      // Finished reading a header
      break;
    }
  }

  String line = client.readStringUntil('\n');
  Serial.print("reply: ");
  Serial.println(line);
  Serial.println("Cerrando la Conexion con IFTTT");
  Serial.println();
}

