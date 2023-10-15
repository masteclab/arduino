#include <Sodaq_RN2483.h>

#define debugSerial SerialUSB
#define loraSerial Serial2

#define NIBBLE_TO_HEX_CHAR(i) ((i <= 9) ? ('0' + i) : ('A' - 10 + i))
#define HIGH_NIBBLE(i) ((i >> 4) & 0x0F)
#define LOW_NIBBLE(i) (i & 0x0F)

//Use OTAA, set to false to use ABP
bool OTAA = false;


////////////////
// ABP//////////
////////////////

// USE YOUR OWN KEYS!
const uint8_t devAddr[4] =
{
    0xcb, 0x26, 0x55, 0x7c
    //cb 26 55 7c
};

// USE YOUR OWN KEYS!
const uint8_t appSKey[16] =
{
  0x2e, 0x05, 0x02, 0x37, 0x71, 0x36, 0xa8, 0x4f, 0xba, 0x4e, 0x07, 0xf5, 0xac, 0xc8, 0x24, 0x5d
  //2e 05 02 37 71 36 a8 4f ba 4e 07 f5 ac c8 24 5d
};

// USE YOUR OWN KEYS!
const uint8_t nwkSKey[16] =
{
  0xad, 0x64, 0x5c, 0xce, 0x43, 0xb4, 0x4e, 0x34, 0x4c, 0xfc, 0x94, 0x05, 0x2a, 0x91, 0x4f, 0x78
  //
};

////////////
// OTAA/////
////////////

// With using the GetHWEUI() function the HWEUI will be used
static uint8_t DevEUI[8]
{
    0x00, 0x04, 0xa3, 0x0b, 0x00, 0x22, 0x93, 0xab
};


const uint8_t AppEUI[8] =
{
    0x4d, 0xe1, 0x0b, 0x63, 0xbb, 0xb4, 0x82, 0xfb
};

const uint8_t AppKey[16] =
//9cb0 1d 26 d6 84 a8 23 65 72 ad 4c 75 08 f6 15
{
    0x9c, 0xb0, 0x1d, 0x26, 0xd6, 0x84, 0xa8, 0x23, 0x65, 0x72, 0xad, 0x4c, 0x75, 0x08, 0xf6, 0x15
};

void setup()
{
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  RED();
  delay(1000);

  while ((!debugSerial) && (millis() < 10000)){
    // Wait 10 seconds for debugSerial to open
  }

  debugSerial.println("Start");

  // Start streams
  debugSerial.begin(57600);
  loraSerial.begin(LoRaBee.getDefaultBaudRate());

  LoRaBee.setDiag(debugSerial); // to use debug remove //DEBUG inside library
  LoRaBee.init(loraSerial, LORA_RESET);

  //Use the Hardware EUI
  getHWEUI();

  // Print the Hardware EUI
  debugSerial.print("LoRa HWEUI: ");
  for (uint8_t i = 0; i < sizeof(DevEUI); i++) {
      debugSerial.print((char)NIBBLE_TO_HEX_CHAR(HIGH_NIBBLE(DevEUI[i])));
      debugSerial.print((char)NIBBLE_TO_HEX_CHAR(LOW_NIBBLE(DevEUI[i])));
  }
  debugSerial.println();  

  setupLoRa();
  BLUE();
}

void setupLoRa(){
  if(!OTAA){
    // ABP
    setupLoRaABP();
  } else {
    //OTAA
    setupLoRaOTAA();
  }
  // Uncomment this line to for the RN2903 with the Actility Network
  // For OTAA update the DEFAULT_FSB in the library
  // LoRaBee.setFsbChannels(1);

  LoRaBee.setSpreadingFactor(9);
}

void setupLoRaABP(){  
  if (LoRaBee.initABP(loraSerial, devAddr, appSKey, nwkSKey, true))
  {
    debugSerial.println("Communication to LoRaBEE successful.");
  }
  else
  {
    debugSerial.println("Communication to LoRaBEE failed!");
  }
}

void setupLoRaOTAA(){

  if (LoRaBee.initOTA(loraSerial, DevEUI, AppEUI, AppKey, true))
  {
    debugSerial.println("Network connection successful.");
  }
  else
  {
    debugSerial.println("Network connection failed!");
  }
}

void loop()
{
  GREEN();
   String reading = getTemperature();
   debugSerial.println(reading);

    switch (LoRaBee.sendReqAck(1, (uint8_t*)reading.c_str(), reading.length(), 2))
    {
    case NoError:
      debugSerial.println("Successful transmission.");
      break;
    case NoResponse:
      debugSerial.println("There was no response from the device.");
      break;
    case Timeout:
      debugSerial.println("Connection timed-out. Check your serial connection to the device! Sleeping for 20sec.");
      delay(20000);
      break;
    case PayloadSizeError:
      debugSerial.println("The size of the payload is greater than allowed. Transmission failed!");
      debugSerial.println(reading);
      break;
    case InternalError:
      debugSerial.println("Oh No! This shouldn't happen. Something is really wrong! The program will reset the RN module.");
      setupLoRa();
      break;
    case Busy:
      debugSerial.println("The device is busy. Sleeping for 10 extra seconds.");
      delay(10000);
      break;
    case NetworkFatalError:
      debugSerial.println("There is a non-recoverable error with the network connection. The program will reset the RN module.");
      setupLoRa();
      break;
    case NotConnected:
      debugSerial.println("The device is not connected to the network. The program will reset the RN module.");
      setupLoRa();
      break;
    case NoAcknowledgment:
      debugSerial.println("There was no acknowledgment sent back!");
      break;
    default:
      break;
    }
    // Delay between readings
    // 60 000 = 1 minute
    BLUE();
    delay(600000); 
}

String getTemperature()
{
  String payload="AQ2#";
  //10mV per C, 0C is 500mV
  float mVolts = (float)analogRead(TEMP_SENSOR) * 3300.0 / 1023.0;
  float temp = (mVolts - 500.0) / 10.0;
  payload = payload + String(temp) + ",0.0#$";

  return payload;
}

/**
* Gets and stores the LoRa module's HWEUI/
*/
static void getHWEUI()
{
    uint8_t len = LoRaBee.getHWEUI(DevEUI, sizeof(DevEUI));
}

void RED() {
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_BLUE, HIGH);
}

void GREEN() {
  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_BLUE, HIGH);
}

void BLUE() {
  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_BLUE, LOW);
}
