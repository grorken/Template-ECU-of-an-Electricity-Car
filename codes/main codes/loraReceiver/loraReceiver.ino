#include "LoRa_E32.h"
#include <SoftwareSerial.h>
 
SoftwareSerial mySerial(10, 11);
 
/*
   Pinler     Arduino Nano    Lora E32 433T20d
                  11                3
                  10                4
*/
 
LoRa_E32 e32ttl(&mySerial);

struct Signal {
//  char type[15] = "Fixaj.com";
  byte temp[4];
  byte zaman[4];
  byte hiz[4];
  byte sicaklik[4];
  byte sonhucre[4];
  //byte volt[4];
} data;
 
 
void setup() {
  Serial.begin(9600);
  e32ttl.begin();
  delay(500);
}
 
void loop() {
 
  ResponseStatus rs = e32ttl.sendFixedMessage(0, 44, 23, &data, sizeof(Signal));
  Serial.println(rs.getResponseDescription());
 
  delay(2000);
 
  while (e32ttl.available()  > 1) {
   // for(int i=0;i<5;i++){
  ResponseStructContainer rsc = e32ttl.receiveMessage(sizeof(Signal));
    struct Signal data = *(Signal*) rsc.data;
//        Serial.print("Yer: ");
//    Serial.println(data.type);
//        Serial.print("Ortam Sıcaklığı: ");
    Serial.print(*(float*)(data.temp));
        Serial.print("/");
    Serial.print(*(float*)(data.zaman));
        Serial.print("/");
    Serial.print(*(float*)(data.hiz));
        Serial.print("/");
    Serial.print(*(float*)(data.sicaklik));
        Serial.print("/");
    Serial.print(*(float*)(data.sonhucre));
//        Serial.print("/");
//    Serial.print(*(float*)(data.volt));
       
        Serial.println("");       
    rsc.close();
    delay(200);
 //   }
 //   Serial.println("");
  }
}
