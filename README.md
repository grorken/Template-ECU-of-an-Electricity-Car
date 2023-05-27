# Template-ECU-of-an-Electricity-Car
Taslak-TÜBİTAK EFFICIENCY CHALLANGE yarışması için Elektrikli Araçların Araç Kontrol Sistemi
Template-Electricity Car ECU for TÜBİTAK EFFICIENCY CHALLANGE


EN

Hello everyone . I would like to share the ECU template works that I made in 2023 here for future students, both university and high school students, to have a template and get ideas. Because I know that Knowledge will multiply as it is shared.
Features:

- Data Communication with the computer and data recording
- Dashboard
- Cells Voltage Reading
- Temperature Reading of Cells
- Battery Capacity Measurement
- Charging Power Measurement
- Critical Temperature detection and prevention
- Wiper-horn etc. operation with CanBUS system


In general (without pieces) Ingredients:

- MCP2515

- LoRa E32

- Arduino Mega 2560

- Arduino Uno R3

- DS18B20 Temperature Sensor

- CD74HC4067 4-Bit MUX

- Fan

- Buzzer

- Contactor

- Nextion Display (P043)

-Reed Relay

Arduino MEGA 2560 LoRa, Nextion, Temperature and Voltage reading, Fan, Buzzer, Contactor tasks;

Arduino Uno R3 is used for CanBus System. MCP2515 is used for CanBUS. Only relay control is performed in CanBUS.

Voltage reading is filtered with opamps. Our battery was 17 Series. Instead of making 17 connections to Arduino, we connected to MUX and solved the problem with a single connection.

The Temperature Sensor is likewise reduced to a single pin instead of using multiple pins. But this time it was made using OneWire.h library.

Speed is measuring using magnet and reed relay. When the reed relay sees the magnet, input to arduino is HIGH. And there was a timer which is counting the laps.

There were certain delays as there were too many tasks to be loaded with a single processor. This resulted in the communication system LORA not being able to capture the data. Although I added delay(s) in different places, I could not solve it.




TR

Herkese merhaba arkadaşlar. 2023 Senesinde yapmış olduğum ECU taslak çalışmalarını gelecekte yarışacak gerek üniversite gerek de lise öğrencileri için taslak olması ve fikir almaları için burada paylaşmak istiyorum. Çünkü Bilginin paylaştıkça çoğalacağını biliyorum.
Özellikler:

- Bilgisayar ile Veri Haberleşmesi ve verilerin kaydedilmesi
- Gösterge Paneli
- Hücrelerin Voltaj Okuması
- Hücrelerin Sıcaklık Okuması
- Batarya Kapasitesi Ölçümü
- Şarj Gücü Ölçümü
- Kritik Sıcaklık tespiti ve önlenmesi
- CanBUS sistemi ile silecek-korna vs çalıştırma


Genel olarak(adet olmadan) Malzemeler:

- MCP2515

- LoRa E32

- Arduino Mega 2560

- Arduino Uno R3

- DS18B20 Sıcaklık Sensörü

- CD74HC4067 4 Bit MUX

- Fan

- Buzzer

- Kontaktör

- Nextion Ekran (P043)


Arduino MEGA 2560 LoRa, Nextion, Sıcaklık ve Voltaj okuma, Fan, Buzzer, Kontaktör görevlerinde;

Arduino Uno R3 ise CanBus Sistemi için kullanılmıştır. CanBUS için MCP2515 kullanılmıştır. CanBUS'ta sadece röle kontrolü yapılmaktadır.

Voltaj okuma Opamplarla filtrelenip yapılmaktadır. Bataryamız 17 Seriydi. Arduinoya 17 tane bağlantı yapmak yerine MUX 'a bağlayıp tek bağlantı ile işi çözdük.

Sıcaklık Sensörü de aynı şekilde birden fazla pin kullanmaktansa tek pine indirilmiştir. Fakat bu sefer OneWire.h kütüphanesi kullanılarak yapılmıştır.

Tek işlemci ile çok fazla görev yüklenmesi olduğundan belli gecikmeler meydana gelmişti. Bu da haberleşme Sistemi LORA'nın verileri yakalayamaması ile sonuçlandı. Farklı yerlere delay(lar) eklememe rağmen çözememiştim.
