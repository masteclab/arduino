|#include <LiquidCrystal.h>

String deveui = "0004A30B0022A115";
String appeui = "70B3D57ED0016CC6";
String appkey = "c64bd21a37bbb8d1e61b8b7bd2281e60";
String nwkskey = "7afc290194ca8b6b841119f2d48bdba1";
String appskey = "60cc7de24f91180973e17ce8023137d0";
bool otaa = true;


void setup() {
  Serial.begin(115200);

}

void loop() {
  if(otaa)
  {
    Serial.print("-DevEui: ");
    Serial.println(deveui);
    Serial.println("BigEndian:");
    for(int i = 0; i<16; i=i+2)
    {
      Serial.print("0x");
      Serial.print(deveui[i]);
      Serial.print(deveui[i+1]);
      Serial.print(", ");
    }
    Serial.println(" ");
    Serial.println("LittleEndian:");
    for(int i = 0; i<16; i=i+2)
    {
      Serial.print("0x");
      Serial.print(deveui[14-i]);
      Serial.print(deveui[15-i]);
      Serial.print(", ");
    }
    Serial.println(" ");

    Serial.print("-AppEui: ");
    Serial.println(appeui);
    Serial.println("BigEndian:");
    for(int i = 0; i<16; i=i+2)
    {
      Serial.print("0x");
      Serial.print(appeui[i]);
      Serial.print(appeui[i+1]);
      Serial.print(", ");
    }
    Serial.println(" ");
    Serial.println("LittleEndian:");
    for(int i = 0; i<16; i=i+2)
    {
      Serial.print("0x");
      Serial.print(appeui[14-i]);
      Serial.print(appeui[15-i]);
      Serial.print(", ");
    }
    Serial.println(" ");

    Serial.print("-AppKey: ");
    Serial.println(appkey);
    Serial.println("BigEndian:");
    for(int i = 0; i<32; i=i+2)
    {
      Serial.print("0x");
      Serial.print(appkey[i]);
      Serial.print(appkey[i+1]);
      Serial.print(", ");
    }
    Serial.println(" ");
    Serial.println("LittleEndian:");
    for(int i = 0; i<32; i=i+2)
    {
      Serial.print("0x");
      Serial.print(appkey[30-i]);
      Serial.print(appkey[31-i]);
      Serial.print(", ");
    }
    Serial.println(" ");
    
  }
  else
  {
    Serial.print("-DevEui: ");
    Serial.println(deveui);
    Serial.println("BigEndian:");
    for(int i = 0; i<16; i=i+2)
    {
      Serial.print("0x");
      Serial.print(deveui[i]);
      Serial.print(deveui[i+1]);
      Serial.print(", ");
    }
    Serial.println(" ");
    Serial.println("LittleEndian:");
    for(int i = 0; i<16; i=i+2)
    {
      Serial.print("0x");
      Serial.print(deveui[14-i]);
      Serial.print(deveui[15-i]);
      Serial.print(", ");
    }
    Serial.println(" ");

    Serial.print("-NwkSKey: ");
    Serial.println(nwkskey);
    Serial.println("BigEndian:");
    for(int i = 0; i<32; i=i+2)
    {
      Serial.print("0x");
      Serial.print(nwkskey[i]);
      Serial.print(nwkskey[i+1]);
      Serial.print(", ");
    }
    Serial.println(" ");
    Serial.println("LittleEndian:");
    for(int i = 0; i<32; i=i+2)
    {
      Serial.print("0x");
      Serial.print(nwkskey[30-i]);
      Serial.print(nwkskey[31-i]);
      Serial.print(", ");
    }
    Serial.println(" ");

    Serial.print("-AppSKey: ");
    Serial.println(appskey);
    Serial.println("BigEndian:");
    for(int i = 0; i<32; i=i+2)
    {
      Serial.print("0x");
      Serial.print(appskey[i]);
      Serial.print(appskey[i+1]);
      Serial.print(", ");
    }
    Serial.println(" ");
    Serial.println("LittleEndian:");
    for(int i = 0; i<32; i=i+2)
    {
      Serial.print("0x");
      Serial.print(appskey[30-i]);
      Serial.print(appskey[31-i]);
      Serial.print(", ");
    }
    Serial.println(" ");
  }
  
  while(1);
}
