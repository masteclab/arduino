#include <Arduino.h>
#include <MHZ19.h>
#include <SoftwareSerial.h>                                //  Remove if using HardwareSerial or non-uno compatabile device

#define RX_PIN 16
#define TX_PIN 17
#define BAUDRATE 9600                                      // Native to the sensor (do not change)

MHZ19 myMHZ19;
//SoftwareSerial mySerial(RX_PIN, TX_PIN);                   // Uno example
HardwareSerial mySerial(1);
unsigned long getDataTimer = 0;

void setRange(int range);                          

void setup()
{
    Serial.begin(115200);

    //mySerial.begin(BAUDRATE);                                // Uno Exammple: Begin Stream with MHZ19 baudrate
    mySerial.begin(BAUDRATE, SERIAL_8N1, RX_PIN, TX_PIN);
    myMHZ19.printCommunication();                            // Error Codes are also included here if found (mainly for debugging/interest)
    myMHZ19.begin(mySerial);                                 // *Important, Pass your Stream reference
    myMHZ19.autoCalibration();
}

void loop()
{

    if (millis() - getDataTimer >= 2000)               
    {
        int CO2;                                        // Buffer for CO2
        CO2 = myMHZ19.getCO2();                         // Request CO2 (as ppm)

        if(myMHZ19.errorCode == RESULT_OK)              // RESULT_OK is an alis for 1. Either can be used to confirm the response was OK.
        {
            Serial.print("CO2 Value successfully Recieved: ");
            Serial.println(CO2);
            Serial.print("Response Code: ");
            Serial.println(myMHZ19.errorCode);          // Get the Error Code value
        }

        else 
        {
            Serial.println("Failed to recieve CO2 value - Error");
            Serial.print("Response Code: ");
            Serial.println(myMHZ19.errorCode);          // Get the Error Code value
        }  

        getDataTimer = millis();                            
    }
}
