#include <SPI.h> //Library for using SPI Communication
#include <mcp2515.h> //Library for using CAN Communication

//#define ldr A1

struct can_frame canMsg;
MCP2515 mcp2515(10);

void setup(){
  while (!Serial);
  Serial.begin(9600);
  SPI.begin(); //Begins SPI communication
 //Begins to read temperature & humidity sensor value
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ); //Sets CAN at speed 500KBPS and Clock 8MHz
  mcp2515.setNormalMode();
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  }

void loop(){
  int korna = digitalRead(2);
  int silecek = digitalRead(3);
  int kisaFar = digitalRead(4);
  int uzunFar = digitalRead(5);
  int sagSinyal = digitalRead(6);  
  int solSinyal = digitalRead(7);  
  
  Serial.print("korna:");
  Serial.println(korna);
  
  Serial.print("silecek:");
    Serial.println(silecek);
    
  Serial.print("kisaFar:");
    Serial.println(kisaFar);

  Serial.print("uzunFar:");
    Serial.println(uzunFar);

  Serial.print("sagSinyal:");
    Serial.println(sagSinyal);

  Serial.print("solSinyal:");
    Serial.println(solSinyal);

  Serial.println("-----------------------------------------");
 // delay(100);

  

  canMsg.can_id = 0x036; //CAN id as 0x036
  canMsg.can_dlc = 8; //CAN data length as 8
  canMsg.data[0] = korna; //Update humidity value in [0]
  canMsg.data[1] = silecek; //Update temperature value in [1]
  canMsg.data[2] = kisaFar; //Rest all with 0
  canMsg.data[3] = uzunFar;
  canMsg.data[4] = sagSinyal;
  canMsg.data[5] = solSinyal;
  canMsg.data[6] = 0x00;
  canMsg.data[7] = 0x00;
  mcp2515.sendMessage(&canMsg); //Sends the CAN message
  delay(100);
}
