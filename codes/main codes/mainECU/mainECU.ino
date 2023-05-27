#include "Nextion.h"
// Master RX, TX, connect to Nextion TX, RX
//SoftwareSerial HMISerial(10, 11);



//for sd card
#include <SoftwareSerial.h>
#include <SPI.h>
#include <SD.h>
unsigned long sure; //millis denemesi
const int chipSelect = 53;
File dosya;

bool flagTemp=0;
bool flagCurrent=0;

            //      HIZ ÖLÇÜMÜ

//calculations
//tire radius ~ 13.5 inches
//circumference = pi*2*r =~85 inches
//max speed of 35mph =~ 616inches/second
//max rps =~7.25

int reed =3;//pin connected to read switch

//storage variables
int reedVal;
long timer;// time between one full rotation (in ms)
float mph;
float radius = 50.64;// tire radius (in inches)
float circumference;

int maxReedCounter = 100;//min time (in ms) of one rotation (for debouncing)
int reedCounter;




int hizOku=0;

bool flag=0;

float sonHucre=0;

float vB[17]={2.04337,  4.29093, 5.98078, 7.74423, 10.28571,  11.69613,  14.23631,  15.96153,  17.40679,  20.00000,  22.68264,  24.1163, 25.70145, 28.84727,  29.61301,  31.97227,  34.2418};
float cellV[17];



#define acsBattery A6
#define acsChargePower A7
const float vcc = 5.00;
const float factor = 0.02;

float voltage4;
float voltage3;

//for temperature
#include <OneWire.h>
#include <DallasTemperature.h>

// Master RX, TX, connect to Nextion TX, RX
//SoftwareSerial HMISerial(10, 11);





//dongu:
//
//digitalWrite(10,HIGH);
//
//
//while(10){
//  for (int i = 0;  i < deviceCount;  i++)
//  {
//    tempC[i] = {sensors.getTempCByIndex(i)};
//    if(tempC[i]>=70){
//            digitalWrite(10,HIGH); //KONTAKTÖR
//        }
//        else{
//            digitalWrite(10,LOW);//KONTAKTÖR
//        }
//  }
//}
//
//
//
//dongeri:
//
//
//
//return *dongeri;






// Data wire is plugged into digital pin 2 on the Arduino
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire device
OneWire oneWire(ONE_WIRE_BUS);  

// Pass oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);

int deviceCount = 0;
float tempC[5];

int s0 = 2;
int s1 = 3;
int s2 = 4;
int s3 = 5;

float val2 = analogRead(A1);
float voltage2 = (val2*5.0)/1024.0;


int SIG_pin = A0;

NexNumber n10 = NexNumber(2, 21, "x0"); //        BATARYA SICAKLIK
NexNumber n11 = NexNumber(2, 38, "x1"); //        BATARYA SICAKLIK
NexNumber n12 = NexNumber(2, 39, "x2"); //        BATARYA SICAKLIK
NexNumber n13 = NexNumber(2, 40, "x3"); //        BATARYA SICAKLIK
NexNumber n14 = NexNumber(2, 41, "x4"); //       BATARYA SICAKLIK



//NexNumber n13 = NexNumber(1, 18, "x0"); //       boş
NexNumber n48 = NexNumber(1, 19, "x0"); //       SICAKLIK İBRELİ
NexNumber n15 = NexNumber(1, 20, "x50"); //       ŞARJ GÜCÜ
NexNumber n16 = NexNumber(1, 21, "x3"); //       KALAN ENERJİ MİKTARI
NexNumber n17 = NexNumber(1, 22, "n4"); //       boş

NexProgressBar j0 = NexProgressBar(1,1,"j0");//   ANA HARKETLİ GÖSTERGE
NexGauge z1= NexGauge(1,8,"z1");//                İBRE SICAKLIK
NexGauge z2= NexGauge(1,9,"z2");//                İBRE ŞARJ GÜCÜ

NexNumber n0 = NexNumber(1,4,"n0"); // HIZ GÖSTERGESİ

NexNumber n33 = NexNumber(2, 38, "x21"); //       BATARYA VOLTAJ
NexNumber n34 = NexNumber(2, 39, "x20"); //       BATARYA VOLTAJ
NexNumber n18 = NexNumber(2, 23, "x5"); //       BATARYA VOLTAJ
NexNumber n19 = NexNumber(2, 40, "x6"); //       BATARYA VOLTAJ
NexNumber n20 = NexNumber(2, 41, "x7"); //       BATARYA VOLTAJ
NexNumber n21 = NexNumber(2, 26, "x8"); //       BATARYA VOLTAJ
NexNumber n22 = NexNumber(2, 27, "x9"); //       BATARYA VOLTAJ
NexNumber n23 = NexNumber(2, 28, "x10"); //       BATARYA VOLTAJ
NexNumber n24 = NexNumber(2, 29, "x11"); //       BATARYA VOLTAJ
NexNumber n25 = NexNumber(2, 30, "x12"); //       BATARYA VOLTAJ
NexNumber n26 = NexNumber(2, 31, "x13"); //       BATARYA VOLTAJ
NexNumber n27 = NexNumber(2, 32, "x14"); //       BATARYA VOLTAJ
NexNumber n28 = NexNumber(2, 33, "x15"); //       BATARYA VOLTAJ
NexNumber n29 = NexNumber(2, 34, "x16"); //       BATARYA VOLTAJ
NexNumber n30 = NexNumber(2, 35, "x17"); //       BATARYA VOLTAJ
NexNumber n31 = NexNumber(2, 36, "x18"); //       BATARYA VOLTAJ
NexNumber n32 = NexNumber(2, 37, "x19"); //       BATARYA VOLTAJ



//uint32_t butondurum = 0;

float okuMux(int kanal){
  int controlPin[] = {s0, s1, s2, s3};

  int muxkanal[16][4]={
    {0,0,0,0}, //kanal 0
    {1,0,0,0}, //kanal 1
    {0,1,0,0}, //kanal 2
    {1,1,0,0}, //kanal 3
    {0,0,1,0}, //kanal 4
    {1,0,1,0}, //kanal 5
    {0,1,1,0}, //kanal 6
    {1,1,1,0}, //kanal 7
    {0,0,0,1}, //kanal 8
    {1,0,0,1}, //kanal 9
    {0,1,0,1}, //kanal 10
    {1,1,0,1}, //kanal 11
    {0,0,1,1}, //kanal 12
    {1,0,1,1}, //kanal 13
    {0,1,1,1}, //kanal 14
    {1,1,1,1}  //kanal 15
  };


  for(int i = 0; i < 4; i ++){

    delay(20);
    digitalWrite(controlPin[i], muxkanal[kanal][i]);
  }


  int val = analogRead(SIG_pin);
  float voltage = (val*5.0)/1024.0;
  return voltage;
}




//#define TRIGGER_PIN 9
//#define ECHO_PIN 10

void setup()
{
/*      TASLAK KISMI BAŞLAR

hizOku=digitalRead(3);




      TASLAK KISMI BİTER*/
 
  /* Set the baudrate which is for debug and communicate with Nextion screen. */
  dbSerialPrintln("setup begin");
  nexInit();
  dbSerialPrintln("setup done");


//        HIZ ÖLÇME  

reedCounter = maxReedCounter;
  circumference = 2*3.14*radius;
  pinMode(reed, INPUT);
  

  cli();//stop interrupts

  //set timer1 interrupt at 1kHz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;
  // set timer count for 1khz increments
  OCR1A = 1999;// = (1/1000) / ((1/(16*10^6))*8) - 1
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS11 bit for 8 prescaler
  TCCR1B |= (1 << CS11);   
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  
  sei();//allow interrupts
  //END TIMER SETUP
  


 // Serial2.begin(9600);

   sensors.begin();  // Start up the library
 
  Serial.begin(9600);

  
  // locate devices on the bus
  Serial.print("Locating devices...");
  Serial.print("Found ");
  deviceCount = sensors.getDeviceCount();
  Serial.print(deviceCount, DEC);
  Serial.println(" devices.");
  Serial.println("");
  
  Serial.print("Initializing SD card...");

  if (!SD.begin(53)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
  pinMode(A4,INPUT);


  pinMode(s0, OUTPUT); 
  pinMode(s1, OUTPUT); 
  pinMode(s2, OUTPUT); 
  pinMode(s3, OUTPUT); 

  pinMode(11,OUTPUT);

  pinMode(A6,INPUT);
  pinMode(A7,INPUT);

  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);

  pinMode(13,OUTPUT);

  digitalWrite(s0, LOW);
  digitalWrite(s1, LOW);
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);

  

  Serial.begin(9600);
}

// FUNCTİONS START


          //          HIZ ÖLÇME

    ISR(TIMER1_COMPA_vect) {//Interrupt at freq of 1kHz to measure reed switch
  reedVal = digitalRead(reed);//get val of A0
  if (reedVal){//if reed switch is closed
    if (reedCounter == 0){//min time between pulses has passed
      mph = (56.8*float(circumference))/float(timer);//calculate miles per hour
      timer = 0;//reset timer
      reedCounter = maxReedCounter;//reset reedCounter
    }
    else{
      if (reedCounter > 0){//don't let reedCounter go negative
        reedCounter -= 1;//decrement reedCounter
      }
    }
  }
  else{//if reed switch is open
    if (reedCounter > 0){//don't let reedCounter go negative
      reedCounter -= 1;//decrement reedCounter
    }
  }
  if (timer > 3000){
    mph = 0;//if no new pulses from reed switch- tire is still, set mph to 0
  }
  else{
    timer += 1;//increment timer
  } 
}

void displayMPH(){
  if(mph>=75){
    Serial.print("HIZ:  ");
    Serial.println(20.1);
  }
  else{
     Serial.print("HIZ:  ");
     Serial.println(mph);
  }
 
}



// FUNCTİONS END








void loop(void)
{

//  bt0.getValue(&butondurum);   nextiondaki veriyi çekme
//  delay(200);


displayMPH();
 n0.setValue(mph);


digitalWrite(11,HIGH);//transistor tetik
digitalWrite(13,HIGH);
sure=sure+5;
        //    SICAKLIK
 sensors.requestTemperatures();
for (int i = 0;  i < deviceCount;  i++)
  {
    tempC[i] = {sensors.getTempCByIndex(i)};
    Serial.print(tempC[i]);
    Serial.print("/");

    
    displayMPH();
     n0.setValue(mph);


//      UYARI
    if(tempC[i]>=55){
        digitalWrite(8,HIGH);//FAN
        digitalWrite(9,HIGH);//BUZZER

        
        displayMPH();
         n0.setValue(mph);

       
        if(tempC[i]>=70){
            digitalWrite(10,HIGH); //KONTAKTÖR
        }
        else{
            digitalWrite(10,LOW);//KONTAKTÖR
        }
    }
    else{
        digitalWrite(8,LOW);//FAN
        digitalWrite(9,LOW);//BUZZER
    }

    n10.setValue(tempC[0]*100);
    n11.setValue(tempC[1]*100);
    n12.setValue(tempC[2]*100);
    n13.setValue(tempC[3]*100);
    n14.setValue(tempC[4]*100); 

  }  
        //   VOLTAJ OKUMA
  for(int i = 0; i < 16; i ++){
//    Serial.print(i);
//    Serial.print(".KANALDAKİ DEĞER");

   
    displayMPH();
     n0.setValue(mph);


    cellV[0]=okuMux(0)*vB[0];
    cellV[i+1]=okuMux(i+2)*vB[i+2]-okuMux(i+1)*vB[i+1];
    Serial.print(cellV[i]);
    
//    Serial.print("");
//    Serial.print(okuMux(i)*vB[i]);
    Serial.print("/");
    delay(20);
  }
  val2 = analogRead(A1);
  voltage2 = (val2*5.0)/1024.0;
  Serial.print(voltage2*34.5018);
  Serial.println("");


  displayMPH();
   n0.setValue(mph);


//      ACS758 FOR CHARGE POWER
voltage3=(5.0/1023.0)*analogRead(acsChargePower);
 voltage3= voltage3-(vcc*0.5)+0.007;

 float current2=voltage3/factor;

 float  power=voltage3*current2;
 Serial.print(power,2);
//      
  if(current2>=40){

    
    displayMPH();
     n0.setValue(mph);

    
        digitalWrite(8,HIGH);//FAN
        digitalWrite(9,HIGH);//BUZZER
        if(current2>=60){
            digitalWrite(10,HIGH); //KONTAKTÖR
        }
        else{
            digitalWrite(10,LOW);//KONTAKTÖR
        }
    }
    else{
        digitalWrite(8,LOW);//FAN
        digitalWrite(9,LOW);//BUZZER
    }
 

      displayMPH();
       n0.setValue(mph);


//      ACS758 FOR BATTERY CURRENT
 voltage4=(5.0/1023.0)*analogRead(acsBattery);
 voltage4= voltage4-(vcc*0.5)+0.007;

 float current=voltage4/factor;
 Serial.print(current,2);
//      UYARI
  if(current>=40){
        digitalWrite(8,HIGH);//FAN
        digitalWrite(9,HIGH);//BUZZER


        displayMPH();
         n0.setValue(mph);

        
        if(current>=70){
            digitalWrite(10,HIGH); //KONTAKTÖR
            while(10){
        for (int i = 0;  i < deviceCount;  i++)
        {
          tempC[i] = {sensors.getTempCByIndex(i)};
          if(tempC[i]>=70){
                  digitalWrite(10,HIGH); //KONTAKTÖR
              }
              else{
                  digitalWrite(10,LOW);//KONTAKTÖR
              }
        }
      }
    }
        else{
            digitalWrite(10,LOW);//KONTAKTÖR
        }
    }
    else{
        digitalWrite(8,LOW);//FAN
        digitalWrite(9,LOW);//BUZZER
    }
  

  

  

//SICAKLIK İBRELİ
n48.setValue(tempC[0]);
z1.setValue(tempC[0]);

//ŞARJ GUCU
n15.setValue(708);
z2.setValue(35);

//KALAN ENERJİ MİKTARI  
n16.setValue(voltage2*34.018*28.6);
int yeni= map(voltage2*34.5018,0,63,0,100);
j0.setValue(yeni);


displayMPH();
 n0.setValue(mph);


//VOLTAJ HÜCRELERİ
n18.setValue(cellV[0]);
n19.setValue(cellV[1]);
n20.setValue(cellV[2]);
n21.setValue(cellV[3]);
n22.setValue(cellV[4]);
n23.setValue(cellV[5]);
n24.setValue(cellV[6]);
n25.setValue(cellV[7]);
n26.setValue(cellV[8]);
n27.setValue(cellV[9]);
n28.setValue(cellV[10]);
n29.setValue(cellV[11]);
n30.setValue(cellV[12]);
n31.setValue(cellV[13]);
n32.setValue(cellV[14]);
n33.setValue(cellV[15]);




flag=0;

 sensors.requestTemperatures();

   for (int i = 0;  i < deviceCount;  i++)
  {
    tempC[i] = {sensors.getTempCByIndex(i)};
    Serial.print(tempC[i]);
    Serial.print("/");


    displayMPH();  
     n0.setValue(mph);

    
    n10.setValue(tempC[0]*100);
    n11.setValue(tempC[1]*100);
    n12.setValue(tempC[2]*100);
    n13.setValue(tempC[3]*100);
    n14.setValue(tempC[4]*100);
    
  
  

displayMPH();
 n0.setValue(mph);

  
  //Serial.println("");

 

displayMPH();
 n0.setValue(mph);

      delay(200);
      
      
//      *(float*)(data2.temp) = tempC[0];
//      *(float*)(data2.zaman) = tempC[1];
//      *(float*)(data2.hiz) = tempC[2];
//      *(float*)(data2.sicaklik) = tempC[3];
//      *(float*)(data2.sonhucre) = tempC[4];
 //     *(float*)(data2.volt) = voltage2;


 
  for(int i = 0; i < 16; i ++){
//    Serial.print(i);
//    Serial.print(".KANALDAKİ DEĞER");
    cellV[0]=okuMux(0)*vB[0];


    displayMPH();
     n0.setValue(mph);

    
    cellV[i+1]=okuMux(i+2)*vB[i+2]-okuMux(i+1)*vB[i+1];
    Serial.print(cellV[i]);
    
//    Serial.print("");
//    Serial.print(okuMux(i)*vB[i]);
    Serial.print("/");
    delay(20);
  }
  val2 = analogRead(A1);
  voltage2 = (val2*5.0)/1024.0;
  Serial.print(voltage2*34.5018);


    displayMPH();
     n0.setValue(mph);

  
  sonHucre=map(voltage2,0,60,0,1798);
  Serial.println("");

  //maximumu bul
//int i=0;
//float maxd=vb[0];
//float mind=vb[0];
//int indismax=0;
//int indismin=0;
//  for (i=1;i<16;i++)
//  {
//    if vb[i]>maxd {indismax=i; maxd=vb(i);}
//    if vb[i]<mind {indismin=i; mind=vb(i);}   
//    }

//    İHTİYAÇ OLMAYABİLİR

//n18.setValue(cellV[0]);
//n19.setValue(cellV[1]);
//n20.setValue(cellV[2]);
//n21.setValue(cellV[3]);
//n22.setValue(cellV[4]);
//n23.setValue(cellV[5]);
//n24.setValue(cellV[6]);
//n25.setValue(cellV[7]);
//n26.setValue(cellV[8]);
//n27.setValue(cellV[9]);
//n28.setValue(cellV[10]);
//n29.setValue(cellV[11]);
//n30.setValue(cellV[12]);
//n31.setValue(cellV[13]);
//n32.setValue(cellV[14]);
//n33.setValue(cellV[15]);
  



      displayMPH();
       n0.setValue(mph);

      
      dosya = SD.open("test.txt");
  if (dosya) {
    Serial.println("test.txt:");
  displayMPH();
   n0.setValue(mph);

    // read from the file until there's nothing else in it:
    while (dosya.available()) {
      Serial.write(dosya.read());
    }
    // close the file:
    dosya.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
    }
   
  
 


    displayMPH();
     n0.setValue(mph);

    
    delay(500);
   // sure=54785255;
    dosya = SD.open(String(mph)+String(sonHucre) + ".txt", FILE_WRITE);
    if (dosya) {
    Serial.print(".txt'ye yaziliyor...");
    dosya.println("zaman_ms;hiz_kmh;T_bat_C;V_bat_C;kalan_enerji_Wh");
    dosya.print(sure); // süre değişkeninin içeriğini yeni bir satır olarak dosyaya yazdır.
    dosya.print(";");
    dosya.print(hizOku);
        dosya.print(";");


        displayMPH();
         n0.setValue(mph);


    dosya.print(tempC[3]);
        dosya.print(";");

    dosya.print(voltage2);
        dosya.print(";");

    dosya.print(sonHucre);
    dosya.println("");

    // dosyayı kapat.
//    dosya.close();
//    Serial.println("Yazma tamamlandi.");


    displayMPH();
     n0.setValue(mph);

    
  } else {
    // Eğer dosya açılamadıysa hata mesajı göster.
    Serial.println("Dosya acilamadi.");
  }
  delay(5000); // her 3 saniyede bir tekrar et.

  dosya = SD.open("test.txt");
  if (dosya) {
    Serial.println("test.txt:");

    
      displayMPH();
       n0.setValue(mph);


    // read from the file until there's nothing else in it:
    while (dosya.available()) {
      Serial.write(dosya.read());
    }
    // close the file:
    dosya.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
    }
