#include <SPI.h> //Library for using SPI Communication 
#include <mcp2515.h> //Library for using CAN Communication

struct can_frame canMsg;
MCP2515 mcp2515(10); // SPI CS Pin 10

void setup() {

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);

  SPI.begin();   //Begins SPI communication
  Serial.begin(9600); //Begins Serial Communication at 9600 baud rate
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ); //Sets CAN at speed 500KBPS and Clock 8MHz
  mcp2515.setNormalMode();  //Sets CAN at normal mode
}

void loop() {
  if ((mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) && (canMsg.can_id == 0x036)) {

    int korna = canMsg.data[0];
    int silecek = canMsg.data[1];
    int kisaFar = canMsg.data[2];
    int uzunFar = canMsg.data[3];
    int sagSinyal = canMsg.data[4];
    int solSinyal = canMsg.data[5];


    if (korna == 1) {
      Serial.println("Korna acik");
      digitalWrite(2, HIGH);
    }
    else
    {
      Serial.println("Korna acik degil");
      digitalWrite(2, LOW);

    }
    //    
    if (silecek == 1) {
      Serial.println("silecek acik");

      digitalWrite(3, HIGH);
    }
    else
    {
      Serial.println("silecek acik degil");
            digitalWrite(3, LOW);

    }
    //
    if (kisaFar == 1) {
      Serial.println("kisaFar acik ");

      digitalWrite(4, HIGH);
    }
    else
    {
      Serial.println("kisaFar acik degil");
            digitalWrite(4, LOW);

    }
    //
    if (uzunFar == 1) {
      Serial.println("uzunFar acik ");

      digitalWrite(5, HIGH);
    }
    else
    {
      Serial.println("uzunFar acik degil");
            digitalWrite(5, LOW);

    }
    //
    if (sagSinyal == 1) {
      Serial.println("sagSinyal acik ");

      digitalWrite(6, HIGH);
    }
    else
    {
      Serial.println("sagSinyal acik degil");
            digitalWrite(6, LOW);

    }
    //
    if (solSinyal == 1) {
      Serial.println("solSinyal acik ");

      digitalWrite(7, HIGH);
    }
    else
    {
      Serial.println("solSinyal acik degil");
            digitalWrite(7, LOW);

    }

    Serial.println("--------------------------");


   // delay(100);




    //   if(h==1){
    //     Serial.print("/");
    //     Serial.println(h);
    //     digitalWrite(5,HIGH);
    //     }

    //
    //    Serial.print("/");
    //    Serial.println(y);
    //        Serial.print("/");
    //    Serial.println(z);
    //        Serial.print("/");
    //    Serial.println(h);

  }
}
