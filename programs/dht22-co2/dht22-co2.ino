#include "MHZ19.h"                                        
#include "SoftwareSerial.h"                                    

 

#define RX_PIN 16                                          // Rx pin which the MHZ19 Tx pin is attached to
#define TX_PIN 17                                         // Tx pin which the MHZ19 Rx pin is attached to
#define BAUDRATE 9600                                      // Device to MH-Z19 Serial baudrate (should not be changed)


MHZ19 myMHZ19;                                             // Constructor for library
SoftwareSerial mySerial(RX_PIN, TX_PIN);                   // create device to MH-Z19 serial


void setup()
{
    Serial.begin(115200);                                   // Datenrate serieller Monitor
   
    mySerial.begin(BAUDRATE);                               // (Uno example) device to MH-Z19 serial start   
    myMHZ19.begin(mySerial);                                // *Serial(Stream) refence must be passed to library begin(). 

    myMHZ19.autoCalibration();                              // Turn auto calibration ON (OFF autoCalibration(false))



}

unsigned long getDataTimer = 0;
    
void loop()
{

  if (millis() - getDataTimer >= 2000)
    {

  int  CO2 = myMHZ19.getCO2();                             // Request CO2 (as ppm)
  Serial.print("CO2 (ppm): ");                      
  Serial.println(CO2);                                
                              
  getDataTimer = millis();
    }
}
